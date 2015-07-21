//********************************************************************
//
// Gaowei Chen
// Advanced Operating Systems
// Programming Project #3: Vector clocks MPI simulation
// March 30, 2012
// Instructor: Dr. Ajay K. Katangur
//
//********************************************************************

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

//print out type define
#define sender 1
#define receiver 2
#define normal 3

//vector clock value selection
#define vector_select(a,b) ((a) > (b) ? (a) : (b) )

//print functions
void printExec(int pid);
void printSend(int pid1, int pid2, char* msg);
void printRecv(int pid, int pid2, char* msg);
void printClock(int pid, int* vector_clocks, int size, int type);

// manager and worker functions
void manager(int argc, char** argv, int p);
void worker(int rank, int slaves);

int main(int argc, char** argv)
{
	int id; // process rank
	int p;  // processes number
	int N;  // N slave processes
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
		worker(id, p-1);
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
	char str[200];
	fgets(str,sizeof(str),fp);
	// N slave processes
	int N = atoi(str); // reads number of processes
	if(N != numP-1)
	{
		printf("\n Incorrect number of MPI processes specified.\n Specify -np %d to launch %d slave processes and 1 manager process for simulation\n", N+1, N);
		exit(1);
	}
	printf("\nThere are %d processes in the system\n\n", N);
	int vector_clocks[N];
	const char* delimitor = " ";
	const char* delimitor2 = "\"";
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
			MPI_Recv(vector_clocks, N, MPI_INT, pid, tag_ack, MPI_COMM_WORLD, &status);
			printExec(pid);
			printClock(pid,vector_clocks, N, normal);
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
			MPI_Recv(vector_clocks, N, MPI_INT, pid1, tag_ack, MPI_COMM_WORLD, &status);
			//print out send acknowledgement
			printSend(pid1, pid2, p);
			printClock(pid1,vector_clocks, N, sender);
			//waits for an acknowledgement from the receiver pid2, indicating successful receiving
			MPI_Recv(vector_clocks, N, MPI_INT, pid2, tag_ack, MPI_COMM_WORLD, &status);
			//print out receive acknowledgement
			printRecv(pid1, pid2, p);
			printClock(pid2,vector_clocks, N, receiver);
		}
		else if (strcmp (p,END) == 0)
		{
			printf("---------------\nfinal logical clock at each process.---format: (vector clock)[process id]\n");
			int i,j;
			for(i=1; i<N+1; i++)
			{
				//send an end signal to inform all slave processes to report the logical clock
				MPI_Send(NULL, 0, MPI_INT, i, tag_end, MPI_COMM_WORLD); 
				MPI_Recv(vector_clocks, N, MPI_INT, i, tag_end, MPI_COMM_WORLD, &status);
				printf("(");
				for(j=0; j<N; j++)
				{
					printf("%d",vector_clocks[j]);
					if(j!=N-1)
						printf(",");
				}
				printf(")[%d]\n",i);
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

void worker(int rank, int slaves)
{
	int id = rank-1;
	int ext = 0;
	int logical_clock;
	//number of slave processes, informed by manager process
	MPI_Status status;
	int opt;
	//process' vector clock tick
	int vector_clocks[slaves];
	//temporary vector holds the received vector clocks
	int tmp_compare[slaves];
	int i;
	for(i=0; i<slaves; i++)
		vector_clocks[i] = 0;
	while(!ext)
	{
		MPI_Recv(&opt,1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		switch(status.MPI_TAG)
		{
			case tag_event_exec:
				vector_clocks[id]++;
				MPI_Send(vector_clocks, slaves, MPI_INT, 0, tag_ack, MPI_COMM_WORLD); // acknowledgement
				break;
			case tag_event_send:
				vector_clocks[id]++;
				//sends the clock to opt
				MPI_Send(vector_clocks,slaves, MPI_INT, opt, tag_msg, MPI_COMM_WORLD);
				MPI_Send(vector_clocks, slaves, MPI_INT, 0, tag_ack, MPI_COMM_WORLD); // acknowledgement
				break;
			case tag_event_recv:
				//gets the clock
				MPI_Recv(tmp_compare,slaves, MPI_INT, opt, tag_msg, MPI_COMM_WORLD, &status);
				//vector_clocks[id]++;
				vector_clocks[opt-1]++;
				for(i=0; i<slaves; i++)
					vector_clocks[i]=vector_select(tmp_compare[i], vector_clocks[i]);
				MPI_Send(vector_clocks, slaves, MPI_INT, 0, tag_ack, MPI_COMM_WORLD); // acknowledgement
				break;
			case tag_end:
				MPI_Send(vector_clocks, slaves, MPI_INT, 0, tag_end, MPI_COMM_WORLD); // report final clock
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


void printClock(int pid, int* vector_clocks, int size, int type)
{
	if(type == normal)
		printf( "Logical time at process %d is (", pid );
	else if(type == sender)
		printf( "Logical time at sender process %d is (", pid );
	else if(type == receiver)
		printf( "Logical time at sender process %d is (", pid );
	int i=0;
	for( ;i<size; i++)
	{
		printf("%d",vector_clocks[i]);
		if( i != size-1 )
			printf(",");
	}
	printf(")\n");
}

