//********************************************************************
//
// Xinyi Wang
// Advanced Operating Systems
// Programming Project #3: Logical and Vector Clocks
// Project 3_1: logical clocks
// Date Assigned: Thursday, March 28, 2013
// Due Date: Due Date: Thursday, April 11, 2013 by 9:30 a.m. 
// Instructor: Dr. Ajay K. Katangur
//
//********************************************************************



#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>


//********************************************************************
//
// lamport Function
// --------------
// This function will return the maximum lamport clock value of 
// send and recv event.
// 
//
// Return Value
// ------------
// int                         	maximum logical time                      
//
//
// Value Parameters
// ----------------
// x				int			logical time of its process
// y				int			logical time of other process
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// None
//
//********************************************************************

int lamport(int x, int y) {
	if (x > y) 
		return x;
	else
		return (y+1);
}



//*************************************************************************
//
// OpenFile Function
// -------------
// This function will open the input file from command line, and check
// whether it is available.
// 
//
// Return Value
// ------------
// FILE*                         input file pointer                     
//
//
// Value Parameters
// ----------------
// argc		int    		   				count of command                            
// argv     character array pointer  	content of command   
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// inputfile			FILE*				the file pointer of the input file
//
//************************************************************************

FILE *OpenFile(int argc, char *argv[]) {
		
		FILE *inputfile;
		
		if (argc < 2) {
				fprintf(stderr, "usage: mpirun -np n(number of processes) aosproj3_2 inputfile\n");
				fprintf(stderr, "invalid input file: %s\n", argv[1]);
				exit(0);
			}
		
		inputfile = fopen(argv[1], "r");  // open the file from command line to read
		
		if (inputfile == NULL) {
		   printf("can't open inputfile for reading. \n");
		   exit(0);
		}
		
		return inputfile;
}



//*************************************************************************
//
// master Function
// -------------
// This function will use rank 0 as master to read from the input file, and
// send the information to slaves and recv the logical time from the slaves
// according to the event type.
// 
//
// Return Value
// ------------
// void                         does not return any value                     
//
//
// Value Parameters
// ----------------
// argc		int    		   				count of command                            
// argv     character array pointer  	content of command
// nprocs	int*						number of processes   
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// fp				FILE*				the file pointer of the input file
// N				int					the number of the slaves processes
// logical_time		int					lamport logical time
// pid				int					process id of the exec event
// pid1				int					process id of the send event
// pid2				int					process id of the recv event
// i				int 				loop counter for master and slaves comm
// read_track		char*				some block of string delimited by some delimiter
// strline			char[]				string to store each line of the input file
//
//************************************************************************

void master(int argc, char *argv[], int *nprocs) {
	FILE *fp;
	fp = OpenFile(argc, argv);
	
	int N, logical_time = 0;
	int pid, pid1, pid2;
	int i;
	char *read_track;
	char strline[999]; // each line of the string
	
	fgets(strline,sizeof(strline),fp); // get the first line 
	N = atoi(strline); // reads number of processes as N
	
	if((*nprocs) != N + 1) // number of processes doesn't match
	{
		fprintf(stderr, "We need %d processes for this simulation.\nTherefore, usage: mpirun -np %d %s %s\n", N+1, N+1, argv[0], argv[1]);
		fclose(fp);
		exit(0);
	}
	
	MPI_Status status;
	
	printf("-----There are %d processes in the system-----\n", N);
	
	// read the file from second line until EOF
	while(fgets(strline,sizeof(strline),fp) != NULL) {
		
		if(strline[strlen(strline)-1] == '\n') 
			strline[strlen(strline)-1] = 0;
		
		// event type, which is delimited by space			
		read_track = strtok(strline, " ");
		
		if (strcmp (read_track,"exec") == 0) {  // exec event
			// read the process number
			read_track = strtok (NULL," ");
			// assign it to pid
			pid = atoi(read_track);
			// inform the pid to have exec event
			MPI_Send(NULL, 0, MPI_INT, pid, 11, MPI_COMM_WORLD); //tag 11 for exec event
			// wait for the acknowledgement from pid
			MPI_Recv(&logical_time, 1, MPI_INT, pid, 100, MPI_COMM_WORLD, &status); //tag 100 for acknowledgement
			// print out the msg and logical time
			printf( "Execution event in process %d\n", pid );
			printf( "Logical time at process %d is %d\n", pid, logical_time );
		} else if (strcmp (read_track,"send") == 0) {  // send event
				// read the sending process number
				read_track = strtok (NULL," ");
				// assign it to pid1
				pid1 = atoi(read_track);
				// read the recving process number
				read_track = strtok (NULL,"\"");
				// assign it to pid2
				pid2 = atoi(read_track);
				// read the message
				read_track = strtok (NULL,"\"");
				// inform the pid1 to have send event
				MPI_Send(&pid2, 1, MPI_INT, pid1, 22, MPI_COMM_WORLD); // tag 22 for send event
				// inform the pid2 to have recv event
				MPI_Send(&pid1, 1, MPI_INT, pid2, 33, MPI_COMM_WORLD); // tag 33 for recv event
				// wait for the acknowledgement from pid1
				MPI_Recv(&logical_time, 1, MPI_INT, pid1, 100, MPI_COMM_WORLD, &status); // tag 100 for acknowledgement
				// print out the msg and logical time for sending
				printf( "Message sent from process %d to process %d: %s\n", pid1, pid2, read_track );
				printf( "Logical time at sender process %d is %d\n", pid1, logical_time );
				// wait for the acknowledgement from pid2
				MPI_Recv(&logical_time, 1, MPI_INT, pid2, 100, MPI_COMM_WORLD, &status); // tag 100 for acknowledgement
				// print out the msg and logical time for recving
				printf( "Message received from process %d by process %d: %s\n", pid1, pid2, read_track );
				printf( "Logical time at receiver process %d is %d\n", pid2, logical_time );
			} else if (strcmp (read_track,"end") == 0) {  //end event
					printf("\n-----Logical time will be printed in ascending task ID order...-----\n");
					// collect the logical time for every slaves
					for(i = 1; i <= N; i++) {
						// inform each slave to send back the final logical time
						MPI_Send(NULL, 0, MPI_INT, i, 99, MPI_COMM_WORLD);  // tag 99 for end event
						// wait for the acknowledgement from each slave
						MPI_Recv(&logical_time, 1, MPI_INT, i, 99, MPI_COMM_WORLD, &status); // tag 99 for end event
						// print them in ascending task ID order
						printf("task ID: %d --- logical time: %d\n", i, logical_time);
					}
					break;
				} else {  // other event handler
						printf("This simulation only supports two event types: exec and send\n");
						fclose(fp);
						exit(0);
					}
		} //end while
	
	fclose(fp);
}



//*************************************************************************
//
// slave Function
// -------------
// This function will use the rest of ranks as slaves to recv the infomation, and
// calculate the logical clock of each process. Then they will send the logical time
// back to the master according to the event type.
// 
//
// Return Value
// ------------
// void                         does not return any value                     
//
//
// Value Parameters
// ----------------
// None
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// slave_id			int					slave process id to know what event to do
// slave_clock		int					slave process clock to record the clock for each event
// lamport_clock	int					lamport logical clock to maximum the clock
//
//************************************************************************

void slave() {
	int slave_id, slave_clock = 0, lamport_clock;
	MPI_Status status;
	
	while(1) {
		MPI_Recv(&slave_id,1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	
		if (status.MPI_TAG == 11) { // tag 11 for exec event
			slave_clock = slave_clock + 1;
			// send the acknowledgement back to master
			MPI_Send(&slave_clock, 1, MPI_INT, 0, 100, MPI_COMM_WORLD); // tag 100 for acknowledgement
		} else if (status.MPI_TAG == 22) { // tag 22 for send event
				slave_clock = slave_clock + 1;
				// send event begins
				MPI_Send(&slave_clock, 1, MPI_INT, slave_id, 23, MPI_COMM_WORLD); // tag 23 for message send and recv event
				// send the acknowledgement back to master
				MPI_Send(&slave_clock, 1, MPI_INT, 0, 100, MPI_COMM_WORLD); // tag 100 for acknowledgement
			} else if (status.MPI_TAG == 33) { // tag 33 for recv event
					// recv event ends
					MPI_Recv(&lamport_clock,1, MPI_INT, slave_id, 23, MPI_COMM_WORLD, &status); // tag 23 for message send and recv event
					slave_clock = slave_clock + 1;
					slave_clock = lamport(slave_clock, lamport_clock);
					// send the acknowledgement back to master
					MPI_Send(&slave_clock, 1, MPI_INT, 0, 100, MPI_COMM_WORLD); // tag 100 for acknowledgement
				} else if (status.MPI_TAG == 99) { // tag 99 for end event
						MPI_Send(&slave_clock, 1, MPI_INT, 0, 99, MPI_COMM_WORLD); // send the master all the logical clock
						break;
					}
	}
}



//*************************************************************************
//
// main Function
// -------------
// This function uses the master and slaves algorithm to simulate the lamport
// logical clock, and reads in a set of simulation parameters and then print
// the logical clocks associated with each event.
// 
//
// Return Value
// ------------
// int                         0 if program works good                     
//
//
// Value Parameters
// ----------------
// argc		int    		   				count of command                            
// argv     character array pointer  	content of command   
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// rank      		int              		process rank
// nprocs			int						number of processes
//
//************************************************************************

int main(int argc, char *argv[]) {
	
	int rank, nprocs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
		master(argc, argv, &nprocs);
	} else {
			slave();
		}
	
	MPI_Finalize();
	return 0;
}


