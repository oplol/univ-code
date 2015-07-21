//********************************************************************
//
// Xinyi Wang
// Advanced Operating Systems
// Programming Project #1: Basic MPI Communication
// Project 1_1: bandwidth of the network
// Date Assigned: Thursday, February 21, 2013
// Due Date: Thursday, March 7, 2013 by 9:30 a.m.
// Instructor: Dr. Ajay K. Katangur
//
//********************************************************************



#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


//********************************************************************
//
// print Function
// --------------
// This function will print out the result to the screen and save it to 
// the file. The message size and the average message passing time will
// be printed to the screen and saved to the file.
// 
//
// Return Value
// ------------
// void                         does not return any value                     
//
//
// Value Parameters
// ----------------
// rank				int*			processes ranks
// message_size		int*			message size
// avg_mp_time		double*			the average message passing time in multiple times
// times			int*			how many times you want to pingpong the message
// fp				FILE*   		the file pointer to store the information of the output file
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

void printTime(int *rank, int *message_size, double *avg_mp_time, int *times, FILE *fp) {
	if ((*rank) == 1) {  // need rank 1 to see the time because of starting and ending at rank 1
				printf("The message size is %d byte, and the average message passing time is %f second. \n", (*message_size)*4, (*avg_mp_time)/(*times));
				fprintf(fp, "%d	%f \n", (*message_size)*4, (*avg_mp_time)/(*times));
				}
}



//*************************************************************************
//
// main Function
// -------------
// This function finds the relationship between latency and the bandwidth
// of the network. The message size and the average message passing time
// will be printed to the screen and saved to the file.
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
// message_size     int              		message size
// count1      		int              		loop count for increasing the message size
// count2			int				 		loop count for the pingpong times
// times			int						how many times you want to pingpong the message
// starttime    	double			 		the starting time
// endtime      	double           		the ending time
// avg_mp_time      double           		the average message passing time in multiple times
// fp				FILE					the file pointer to store the information of the output file
// data				float array pointer		message for pingpong
//
//************************************************************************

int main(int argc, char *argv[]) {
	// local variables
	int rank, message_size, count1, count2, times;
    double starttime, endtime, avg_mp_time = 0;
	FILE *fp;
	fp = fopen("aosproj1_1.txt", "w");  // open the file to write
	
     if (fp == NULL) {
        printf("can't open aosproj1_1.txt for writing. \n");
        exit(0);
     }
	
      MPI_Status status;
      MPI_Init(&argc,&argv);  // MPI Initialization
      MPI_Comm_rank(MPI_COMM_WORLD,&rank);  //Process ID number within the communicator
	  
	  times = 15;
		
			message_size = 1024 * 256;  // message size is increase by 4K each time because of the float type
			float *data[message_size];     // declare the data with the size increasing
			
			for (count2 = 0; count2 < times; count2++) {  //how many times you send and receive the fixed message
			
				if(rank==1) {
				
					starttime = MPI_Wtime();  //starting time right before sending
					
					MPI_Send(data,message_size,MPI_FLOAT,0,100,MPI_COMM_WORLD);  //step1: send data to 0
					MPI_Recv(data,message_size,MPI_FLOAT,0,100,MPI_COMM_WORLD,&status); //step4: recv data from 0
					
					endtime   = MPI_Wtime();  //ending time right after receiving
					
					avg_mp_time = avg_mp_time + (endtime - starttime)/2;  //calculate the average message passing time in multiple times 
					
					} else if (rank == 0) {
					
							MPI_Recv(data,message_size,MPI_FLOAT,1,100,MPI_COMM_WORLD,&status); //step2: recv data from 1
							MPI_Send(data,message_size,MPI_FLOAT,1,100,MPI_COMM_WORLD);  //step3: send data to 1
							
							}
			
			}
			
			printTime(&rank, &message_size, &avg_mp_time, &times, fp);  // print out to the screen and write out to the file
      
      MPI_Finalize();  // MPI finalization
	  
	fclose(fp);  // close the file
	return 0;
}


