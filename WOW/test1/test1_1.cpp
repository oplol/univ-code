#include <mpi.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	int numtasks, rank, index, size;
	double t1, t2, avg;
	ofstream outPut;

	
	outPut.open("test1_1.txt"); 
    	
    MPI_Status Stat;

	MPI_Init (&argc,&argv); //initialize MPI
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for(int i = 0 ; i < 1025 ; i++)  //loop for increasing the size of the message
	{		
		avg = 0;  
		size = i * 1024;
		//char *outmsg; 
	    char *inmsg[size];	

		//inmsg = new char[size];
						        
		//ping pong 10 times
		for(index = 0; index < 100; index++)
		{
			if (rank == 0) //process 0
			{
				//outmsg = new char[size];

				t1 = MPI_Wtime(); //starting time
				
				MPI_Send(inmsg, size, MPI_CHAR, 1, 1, MPI_COMM_WORLD);         
				MPI_Recv(inmsg, size, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &Stat); 

				t2 = MPI_Wtime(); //ending time			
				
				avg += ((t2 - t1) / 2); //average time
				
				//delete [] outmsg;
			}
			else 
				if (rank == 1) //Process 1
				{		
					MPI_Recv(inmsg, size, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &Stat); 					
					MPI_Send(inmsg, size, MPI_CHAR, 0, 1, MPI_COMM_WORLD); 
				}

			
		}				
	
		if(rank == 0)
		{		
			avg /= 10; //average time
		    outPut << size << "   " << avg << endl;
		    cout << size << "   " << avg << endl;
		}
	
		//delete [] inmsg;
		

	}
	MPI_Finalize ();     //finalize MPI
	outPut.close();   
	return (0);
}
