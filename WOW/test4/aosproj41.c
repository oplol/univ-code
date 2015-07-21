//********************************************************************
//
// Xinyi Wang
// Advanced Operating Systems
// Programming Project #4: Chandy-Misra-Haas's Edge Chasing Algorithm
// Date Assigned: Thursday, April 18, 2013
// Due Date: Thursday, May 2, 2013 by 9:30 a.m.
// Instructor: Dr. Ajay K. Katangur
//
//********************************************************************



#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>


/* define struct type probe_message */
typedef struct {
	// id_blocked - ID of process that blocked
	// id_sending - ID of process sending message
	// id_sentto  - ID of process message was sent to
	int id_blocked, id_sending, id_sentto;
	} probe_message;



//********************************************************************
//
// max Function
// --------------
// This function will return the maximum value of any two int numbers.
// 
//
// Return Value
// ------------
// int                         	maximum value of any two int numbers                     
//
//
// Value Parameters
// ----------------
// x				int			the first value
// y				int			the second value
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

int max(int x, int y) {
	if (x > y) 
		return x;
	else
		return y;
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
				fprintf(stderr, "usage: mpirun -np n(number of processes) aosproj4 inputfile\n");
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
// ReadFile Function
// -------------
// This function will read from the input file, and find out the rank which is
// initiating the deadlock detection and the connectivity matrix. Then it will
// print out the rank of processes which is initiating deadlock detection.
//
//
// Return Value
// ------------
// int                         return 1 if read the input file correctly, otherwise 0                     
//
//
// Value Parameters
// ----------------
// argc					int    		   				count of command                            
// argv     			character array pointer  	content of command
// nprocs				int*						number of processes
// detection_starter  	int*						the rank which is initiating the deadlock detection
// connectivity_matrix	int 2d array				the connectivity matrix
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
// i				int 				loop counter for the row of array
// j				int					loop counter for the column of array
// max_process		int					the max rank of any two processes
// theMax			int					the max rank of all the processes
// pid1				int 				id of process sending message
// pid2				int					id of process message was sent to
// read_track		char*				some block of string delimited by some delimiter
// strline			char[]				string to store each line of the input file
//
//************************************************************************

int ReadFile(int argc, char *argv[], int *nprocs, int *detection_starter, int connectivity_matrix[(*nprocs)][(*nprocs)]) {
	FILE *fp;
	fp = OpenFile(argc, argv);
	
	int i, j, max_process, theMax = 0;
	int pid1, pid2;
	char *read_track;
	char strline[999]; // each line of the string
	
	// initialize the connectivity matrix
	for (i = 0; i < (*nprocs); i++) {
		for (j = 0; j < (*nprocs); j++) {
			connectivity_matrix[i][j] = 0;
		}	
	}
	
	while(fgets(strline,sizeof(strline),fp) != NULL) {
		
		if(strline[strlen(strline)-1] == '\n') 
			strline[strlen(strline)-1] = 0;
		
		// read the sending process number	
		read_track = strtok(strline, "-");
		if (read_track != NULL) {
			pid1 = atoi(read_track); // assign it to pid1
			// read the recving process number
			read_track = strtok(NULL, " ");
			if (read_track == NULL) {
				*detection_starter = pid1; // assign the detection starter
			} else {
					pid2 = atoi(read_track); // assign it to pid2
					max_process = max(pid1, pid2); // find the max rank of two processes 
					theMax = max(theMax, max_process); // track the max rank of processes in the entire input file
					// if there is a connection between two processes, then change the corresponding value to 1 in the maxtrix
					connectivity_matrix[pid1][pid2] = 1;
			}
		}
	}
	
	if ((*nprocs) != theMax+1) {
		printf("Error reading input file:\nThe number of processes in the input file doesn't match with the number of processes you entered!\n\n");
		fclose(fp);
		return 0;
	}
	
	fclose(fp);
	
	printf("-----Rank %d is initiating the deadlock detection-----\n", *detection_starter);
	
	return 1;
}



//*************************************************************************
//
// Two2One Function
// -------------
// This function will convert the connectivity matrix into one dimensional array
// for MPI_Scatter.
//
//
// Return Value
// ------------
// void                         does not return any value                     
//
//
// Value Parameters
// ----------------
// nprocs				int*						number of processes
// connectivity_matrix	int 2d array				the connectivity matrix to be converted
// single_matrix		int 1d array				the one dimensional array to be output
//
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// i				int 				loop counter for the row of array
// j				int					loop counter for the column of array
//
//************************************************************************

void Two2One(int *nprocs, int connectivity_matrix[(*nprocs)][(*nprocs)], int single_matrix[(*nprocs)*(*nprocs)]) {
	int i, j;
	for (i = 0; i < (*nprocs); i++) {
		for (j = 0; j < (*nprocs); j++) {
			single_matrix[i*(*nprocs)+j] = connectivity_matrix[i][j];
		}
	}
}



//********************************************************************
//
// CMH_edge_chasing_algorithm function
//
// This function will find out whether the system is deadlock by using
// Chandy-Misra-Haas's edge chasing algorithm. According to the connectivity matrix
// and the rank which is initiating deadlock detection, the ranks will send the probe
// messages to its connected nodes.
//
//
// Return Value
// ------------
// void                         does not return any value                     
//
//
// Value Parameters
// ----------------
// nprocs				int*						number of processes
// rank					int*						process rank
// detection_starter  	int*						the rank which is initiating the deadlock detection
// local_matrix			int 1d array				the one dimensional array for each process
//
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// i				int 				loop counter for each connectivity array 
// check			int					check whether there is any process that the rank can send the message
// loop_controller	int					loop control for jumping out of the while loop
// report_back		int					other processes report back the completion
// message			probe_message		probe_message struct
// probe_type		MPI_Datatype		the new datatype
//
//************************************************************************

void CMH_edge_chasing_algorithm(int *nprocs, int *rank, int *detection_starter, int local_matrix[(*nprocs)]) {
	int i, check = 0;
	int loop_controller = 1;
	int report_back = 0;
	int sum;
	probe_message message;
	
	MPI_Status status;
	
	MPI_Datatype probe_type;  // define the new datatype
	MPI_Type_contiguous(3, MPI_INT, &probe_type);  // the derived datatype
	MPI_Type_commit(&probe_type);  // commit the derived datatype
	
	if ((*rank) == (*detection_starter)) { // the rank which is initiating the deadlock detection
		
		// check whether there is any 1s in the local_matrix for the initial rank
		for (i = 0; i < (*nprocs); i++) {
			if (local_matrix[i] == 1)
				check++;
		}
		
		if (check != 0) {
			// assign the initial value to the struct
			message.id_blocked = (*detection_starter);
			message.id_sending = (*detection_starter);
			
			// sending the message according to the local connectivity matrix
			for (i = 0; i < (*nprocs); i++) {
				if (local_matrix[i] == 1) {
					MPI_Send(&message, 1, probe_type, i, 11, MPI_COMM_WORLD);  // tag 11 for message sending
					message.id_sentto = i;
					printf("PROCESS %d SENDS [%d, %d, %d] TO PROCESS %d.\n", (*rank), message.id_blocked, message.id_sending, message.id_sentto, i);
				}
			}
			
			while(loop_controller) {
				//check whether recv any message from other processes
				MPI_Recv(&message, 1, probe_type, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				if (status.MPI_TAG == 11) {  // if the rank recv the request for keeping sending the probe message
					for (i = 0; i < (*nprocs); i++) {
						if (i != (*rank))
							MPI_Send(NULL, 0, probe_type, i, 33, MPI_COMM_WORLD);  // tag 33 for telling the other processes that there is a deadlock
					}
					printf("-----THE SYSTEM IS DEADLOCKED.-----\n");
					loop_controller = 0;
				} else if (status.MPI_TAG == 22) {  // if the rank recv the completion from other processes
						report_back++;
						if((*nprocs) == report_back + 1) {
							printf("-----THE SYSTEM IS NOT DEADLOCKED.-----\n");
							loop_controller = 0;
						}
					} else if (status.MPI_TAG == 55) {  // if the rank recv acknowledgement from the "end" rank
							for (i = 0; i < (*nprocs); i++) {
							if (i != (*rank))
								MPI_Send(NULL, 0, probe_type, i, 55, MPI_COMM_WORLD);  // tag 55 for telling the other processes the end
							}
							printf("-----THE SYSTEM IS NOT DEADLOCKED.-----\n");
							loop_controller = 0;
						}
			}
		} else {  // if check == 0, it means that there is no associated process
				// sending with tag 44
				for (i = 0; i < (*nprocs); i++) {
						if (i != (*rank))
							MPI_Send(NULL, 0, probe_type, i, 44, MPI_COMM_WORLD);  // tag 44 for telling the other processes that the rank don't have any associated process
				}
				printf("There is no associated process that rank %d can send the probe message.\n", (*detection_starter));
				printf("-----THE SYSTEM IS NOT DEADLOCKED.-----\n");
			}
			
	} else {
			//check whether there is any 1s in the local_matrix for the other processes
			for (i = 0; i < (*nprocs); i++) {
				if (local_matrix[i] == 1)
					check++;
			}
			
			if (check != 0) {
				// recv the probe message for other processes
				MPI_Recv(&message, 1, probe_type, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				
				if (status.MPI_TAG == 11) {   // other processes for keeping sending the probe message
					message.id_sending = (*rank);  // assign the new rank to id_sending
					
					// sending the message according to the local connectivity matrix
					for (i = 0; i < (*nprocs); i++) {
						if (local_matrix[i] == 1) {
							MPI_Send(&message, 1, probe_type, i, 11, MPI_COMM_WORLD);  // tag 11 for message sending
							message.id_sentto = i;
							printf("PROCESS %d SENDS [%d, %d, %d] TO PROCESS %d.\n", (*rank), message.id_blocked, message.id_sending, message.id_sentto, i);
						}
					}
					MPI_Send(NULL, 0, probe_type, (*detection_starter), 22, MPI_COMM_WORLD);  // tag 22 for telling the rank the completion
				}
			} else {  // if check == 0, it means that there is no associated process, and just send back the acknowledgement
					MPI_Recv(&message, 1, probe_type, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					if (status.MPI_TAG == 11)
						MPI_Send(NULL, 0, probe_type, (*detection_starter), 55, MPI_COMM_WORLD);  // tag 55 for telling the rank that i am the "end" rank
				}
		}
}



//*************************************************************************
//
// main Function
// -------------
// This function uses rank 0 to read the input file to get the initial rank
// and the connectivity matrix, and broadcast the rank as the detection starter
// and scatter the connectivity matrix. Finally, detect the deadlock by using
// Chandy-Misra-Haas's edge chasing algorithm.
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
// rank      			int              		process rank
// nprocs				int						number of processes
// detection_starter	int						the rank which is initiating the deadlock detection
// read_flag			int						1 if read the input file correctly, otherwise 0
// connectivity_matrix	int 2d array			2d array to store the connectivity matrix
// single_matrix		int 1d array			1d array converted from connectivity_matrix
// local_matrix			int 1d array			1d array to store the associated process
//
//************************************************************************

int main(int argc, char *argv[]) {
	
	int rank, nprocs, detection_starter;
	int read_flag;
	
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int connectivity_matrix[nprocs][nprocs], single_matrix[nprocs*nprocs], local_matrix[nprocs];
	
	if (rank == 0) {  // rank 0 reads the input file
		read_flag = ReadFile(argc, argv, &nprocs, &detection_starter, connectivity_matrix);  //read the input file
		Two2One(&nprocs, connectivity_matrix, single_matrix);  //convert to 1d array for scattering
	}
	
	MPI_Bcast(&read_flag, 1, MPI_INT, 0, MPI_COMM_WORLD);  //broadcast the read flag
	
	if (read_flag == 1) {
		MPI_Bcast(&detection_starter, 1, MPI_INT, 0, MPI_COMM_WORLD);  //broadcast the rank which is initiating the deadlock detection
		MPI_Scatter(single_matrix, nprocs, MPI_INT, local_matrix, nprocs, MPI_INT, 0, MPI_COMM_WORLD);  //scatter the connectivity_matrix
		MPI_Barrier(MPI_COMM_WORLD);
		
		CMH_edge_chasing_algorithm(&nprocs, &rank, &detection_starter, local_matrix);  // Chandy-Misra-Haas's edge chasing algorithm
	}
	
	MPI_Finalize();
	return 0;
}


