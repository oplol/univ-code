#include <stdio.h>
#include <unistd.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
	int rank, nprocs;
	int i , tag = 10, tag2 = 100, rounds = 2;
	int left, right;
	MPI_Status status;
	
	
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int token = 0;
	int token2 = rounds*nprocs;
	/*
	if (nprocs < 2) {
        printf("Since the number of processes is less than 2, token ring can't be initialized. \n");
        MPI_Finalize();
        return 0;
    }
	*/
    right = (rank + 1) % nprocs;
    left = (nprocs + rank - 1) % nprocs;

    /* Process with rank 0 sends the first token */
    if (rank == 0)
	{
		MPI_Send(&token, 1, MPI_INT, right, tag, MPI_COMM_WORLD);
		//MPI_Send(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD);
	}

	for (i= 0; i < rounds; i++)
	{
		MPI_Recv(&token, 1, MPI_INT, left, tag, MPI_COMM_WORLD, &status);
		//MPI_Recv(&token2, 1, MPI_INT, right, tag2, MPI_COMM_WORLD, &status);
		printf("Rank %3d: received token %2d from rank %3d. (clock-wise) \n", rank, token, left);
		//printf("Rank %3d: received token %2d from rank %3d. (counter clock-wise) \n", rank, token2, right);
		
		
		
		token= token + 1;
		token2 = token2 - 1;
		sleep(1); /* To see the output printed one by one simulating message passing */

		if ((rank != 0) || (i < (rounds - 1)))
		{
			/* Only send it on if we are not rank 0, or there are more rounds to go */
			MPI_Send(&token, 1, MPI_INT, right, tag, MPI_COMM_WORLD);
			//MPI_Send(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}
