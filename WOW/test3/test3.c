#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define events types
#define EXEC "exec"
#define SEND "send"
#define END "end"

//define mpi tags for communication
#define tag_event_exec 111
#define tag_event_send 222
#define tag_event_recv 223
#define tag_msg 225
#define tag_ack 333
#define tag_end 444

//Lamport logical clocks selection
#define lamport(a,b) ((a) > (b) ? (a) : (b + 1))

//print functions
void printExec(int pid);
void printSend(int pid1, int pid2, char* msg);
void printRecv(int pid, int pid2, char* msg);
void printClock(int pid, int logical_time);

// manager and worker functions
void manager(int argc, char** argv, int p);
void worker();

int main(int argc, char** argv)
{
	int id; // process rank
	int p;  // processes number
	MPI_Init(&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &id);
	MPI_Comm_size (MPI_COMM_WORLD, &p);
	// manager worker paradigm requires at least 2 processes
	if( p < 2 )
	{	
		if(id == 0)
			printf("processes must be more than 1.\n");
		exit(1);
	}
	if(id) 
		worker();
	else
		manager(argc, argv, p);
	MPI_Finalize();
}

void manager(int argc, char** argv, int numP)
{
	char* input_file;
	//read input file name
	if( argc < 2)
	{
		printf("input filename not specified, use input instead.\n");
		input_file = "input";
	}
	else
		input_file = argv[1];
	
	//open input file and read line by line 
	FILE *fp;
    fp = fopen(input_file, "r");
    if(!fp) // bail out if file not found
	{
		printf("input file not found. usage -- e.g. mpirun -np 3 a.out input.txt \n");
		exit(1); 
	}
	
	MPI_Status status;
	int N; // N slave processes
	char str[200];
	fgets(str,sizeof(str),fp);
	N = atoi(str); // reads number of processes
	if(N != numP-1)
	{
		printf("\n Incorrect number of MPI processes specified.\n Specify -np %d to launch %d slave processes and 1 manager process for simulation\n", N+1, N);
		exit(1);
	}
	printf("\nThere are %d processes in the system\n\n", N);
	const char* delimitor = " ";
	const char* delimitor2 = "\"";
	int clock_value = 0;
	char* p;
    while(fgets(str,sizeof(str),fp) != NULL)
	{
		int len = strlen(str)-1; // strip trailing '\n' if it exists
		if(str[len] == '\n') 
			str[len] = 0;
		p = strtok (str, delimitor);
		
		// an exec event
		if (strcmp (p,EXEC) == 0)
		{
			p = strtok (NULL,delimitor);
			int pid = atoi(p);
			MPI_Send(NULL, 0, MPI_INT, pid, tag_event_exec, MPI_COMM_WORLD);
			//waits for an acknowledgement
			MPI_Recv(&clock_value, 1, MPI_INT, pid, tag_ack, MPI_COMM_WORLD, &status);
			printExec(pid);
			printClock(pid,clock_value);
		}
		// a send event		
		else if (strcmp (p,SEND) == 0)
		{
			p = strtok (NULL,delimitor);
			int pid1 = atoi(p);
			p = strtok (NULL,delimitor);
			int pid2 = atoi(p);
			p = strtok (NULL,delimitor2); // p -> msg
			//it only simulates. for simplicity, the actual message is not exchanged
			//tell the sender
			MPI_Send(&pid2, 1, MPI_INT, pid1, tag_event_send, MPI_COMM_WORLD);
			//tell the receiver
			MPI_Send(&pid1, 1, MPI_INT, pid2, tag_event_recv, MPI_COMM_WORLD);
			//waits for an acknowledgement from the sender pid1, indicating successful sending
			MPI_Recv(&clock_value, 1, MPI_INT, pid1, tag_ack, MPI_COMM_WORLD, &status);
			//print out send acknowledgement
			printSend(pid1, pid2, p);
			printf( "Logical time at sender process %d is %d\n", pid1, clock_value );
			//waits for an acknowledgement from the receiver pid2, indicating successful receiving
			MPI_Recv(&clock_value, 1, MPI_INT, pid2, tag_ack, MPI_COMM_WORLD, &status);
			//print out receive acknowledgement
			printRecv(pid1, pid2, p);
			printf( "Logical time at receiver process %d is %d\n", pid2, clock_value );
		}
		else if (strcmp (p,END) == 0)
		{
			printf("---------------\nfinal logical clock at each process.---format: logical clock[process id]\n");
			int i;
			for(i=1; i<N+1; i++)
			{
				//send an end signal to inform all slave processes to report the logical clock
				MPI_Send(NULL, 0, MPI_INT, i, tag_end, MPI_COMM_WORLD); 
				MPI_Recv(&clock_value, 1, MPI_INT, i, tag_end, MPI_COMM_WORLD, &status);
				printf("%d[%d] ",clock_value,i);
			}
			printf("\n");
			break;
		}
		else
		{
			printf("input file contains error");
			fclose(fp); //close file
			MPI_Abort(MPI_COMM_WORLD, 1010); //error code 1010 indicates the input file error
			exit(1);
		}
	}
	fclose(fp); //close file

}


void worker()
{
	int ext = 0;
	//process' logical clock tick
	int logical_clock = 0;
	MPI_Status status;
	int opt;
	int opt_clock;
	while(!ext)
	{
		MPI_Recv(&opt,1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		switch(status.MPI_TAG)
		{
			case tag_event_exec:
				logical_clock++;
				MPI_Send(&logical_clock, 1, MPI_INT, 0, tag_ack, MPI_COMM_WORLD);
				break;
			case tag_event_send:
				logical_clock++;
				//sends the clock to opt
				MPI_Send(&logical_clock,1, MPI_INT, opt, tag_msg, MPI_COMM_WORLD);
				MPI_Send(&logical_clock, 1, MPI_INT, 0, tag_ack, MPI_COMM_WORLD); // acknowledgement
				break;
			case tag_event_recv:
				//gets the clock
				MPI_Recv(&opt_clock,1, MPI_INT, opt, tag_msg, MPI_COMM_WORLD, &status);
				logical_clock++;
				logical_clock=lamport(logical_clock, opt_clock);
				MPI_Send(&logical_clock, 1, MPI_INT, 0, tag_ack, MPI_COMM_WORLD); // acknowledgement
				break;
			case tag_end:
				MPI_Send(&logical_clock, 1, MPI_INT, 0, tag_end, MPI_COMM_WORLD); // report final clock
				ext = 1;
		}
	}
	
}

void printExec(int pid)
{
	printf( "Execution event in process %d\n", pid );
}

void printSend(int pid1, int pid2, char* msg)
{
	printf( "Message sent from process %d to process %d: %s\n", pid1, pid2, msg );
}

void printRecv(int pid1, int pid2, char* msg)
{
	printf( "Message received from process %d by process %d: %s\n", pid1, pid2, msg );
}


void printClock(int pid, int logical_time)
{
	printf( "Logical time at process %d is %d\n", pid, logical_time );
}

