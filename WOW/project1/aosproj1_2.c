//********************************************************************
//
// Xinyi Wang
// Advanced Operating Systems
// Programming Project #1: Basic MPI Communication
// Project 1_2: rock-paper-scissors tournament
// Date Assigned: Thursday, February 21, 2013
// Due Date: Thursday, March 7, 2013 by 9:30 a.m.
// Instructor: Dr. Ajay K. Katangur
//
//********************************************************************



#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>


/* define struct type rNv */
typedef struct {
	int r, v;  // r - rank; v - value;
	} rNv;



//********************************************************************
//
// set first round Function
// --------------
// This function will set up the first round and randomize the choices of 
// each process before the start of first round by using MPI_Scatter.
// 
//
// Return Value
// ------------
// void                         does not return any value                     
//
//
// Value Parameters
// ----------------
// rank				int*				processes ranks
// size				int*				how many processes
// value			rNv*				an input pointer array of struct for receive buffer
//           
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// process_value[]	rNv					an array of struct for send buffer
// sndcnt			int					the number of elements sent to each process
// revcnt			int					the number of elements received from root
// i				int					loop count for initializing the process_value
//
//********************************************************************

void setFirstRound(int *rank, int *size, rNv *value) {
	rNv process_value[*size];
	int sndcnt, revcnt, i;
	
	revcnt = 2;
	if (*rank == 0) {
		srand(time(NULL));
		for (i = 0; i < *size; i++) {
			process_value[i].r = i;
			process_value[i].v = rand()%3; 
		}
		sndcnt = 2;
	}
	
	MPI_Scatter(process_value,sndcnt,MPI_INT,value,revcnt,MPI_INT,0,MPI_COMM_WORLD);
	//printf("P:%d = P: %d value is %d\n", *rank, (*value).r , (*value).v);
}



//********************************************************************
//
// Rock Paper Scissors Function
// --------------
// This function is a user-defined reduction operator for rock-paper-scissors, 
// and will find out the winner of each competition. The message will
// be printed to the screen.
// 
//
// Return Value
// ------------
// void                         does not return any value                     
//
//
// Value Parameters
// ----------------
// in				rNv*				an input pointer array of struct with length len
// inout			rNv*				both an input pointer array of struct as well as an output pointer array of struct of length len
// len				int*				an integer indicating the size of a vector length
// datatype			MPI_Datatype*		a handle to the data type that was passed into the call to MPI_REDUCE
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// i				int					loop count for increasing the element of the vector
// rv				rNv					struct type output
//
//********************************************************************

void RockPaperScissors(rNv *in, rNv *inout, int *len, MPI_Datatype *datatype) {
	//int rock = 0, paper = 1, scissors = 2;
	int i;
	rNv rv;
	for (i = 0; i < *len; i++) {
		if (( (*inout).v - (*in).v ) == 1 || ( (*inout).v - (*in).v ) == -2) {
			printf ("Process %d wins over process %d. \n", (*inout).r, (*in).r);fflush(stdout);  // second process wins over first process
			rv.r = (*inout).r;
			rv.v = (*inout).v;
			} else {
				printf ("Process %d wins over process %d. \n", (*in).r, (*inout).r);fflush(stdout);  // first process wins over second process
				rv.r = (*in).r;
				rv.v = (*in).v;
				}
		*inout = rv;
		in++;
		inout++;
	}
}



//*************************************************************************
//
// main Function
// -------------
// This function finds the winner of the rock, paper, scissors tournament
// no matter how many processes you pass in.
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
// rank      		int              		processes ranks
// size     		int              		how many processes
// root				int						root process
// send				rNv						send buffer
// recv				rNv						receive buffer
//
//************************************************************************

int main(int argc, char *argv[]) {
	// local variables
	int rank, size;
	int root = 0;
	rNv send, recv;
	
	MPI_Op myop;
	  MPI_Datatype rNvtype;
	
      MPI_Init(&argc,&argv);  // MPI Initialization
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Process ID number within the communicator
	  MPI_Comm_size(MPI_COMM_WORLD, &size);  // How many processes
	  
	  MPI_Type_contiguous(2, MPI_INT, &rNvtype);
	  MPI_Type_commit(&rNvtype);
	  
	  MPI_Op_create((MPI_User_function *)RockPaperScissors, 0, &myop); // Register the function RockPaperScissors with MPI
	  
	  setFirstRound(&rank, &size, &send);  //set up the first round with random choices
	  //printf("P: %d value is %d\n", send.r, send.v);
	  MPI_Barrier(MPI_COMM_WORLD);
	  MPI_Reduce(&send, &recv, 1, rNvtype, myop, root, MPI_COMM_WORLD);  // Call MPI reduction operation function MPI_Reduce using the registered myop
	  
	  if (rank == root) {
		printf("Process %d wins the rock, paper, scissors tournament. \n", recv.r);fflush(stdout); //print out the final winner
	  }
 
      MPI_Finalize();  // MPI finalization
	
	return 0;
}


