#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, nprocs;
	int i, token1, token2, tag1 = 11, tag2 = 22, rounds, flag1, flag2;
	int left, right;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Status status1, status2;
	MPI_Request reqs1[2], reqs2[2];
	
	if ((rounds = atoi(argv[1])) <= 0) {
			if (rank == 0)
				fprintf(stderr, "invalid rounds: %s\n", argv[1]);
			MPI_Finalize();
			return 0;
        }
	
	token1 = 0;
	token2 = nprocs * rounds;

    right = (rank + 1) % nprocs;
    left = (nprocs + rank - 1) % nprocs;
	
    /* Process with rank 0 sends the first token */
    if (rank == 0)
	{
		MPI_Isend(&token1, 1, MPI_INT, right, tag1, MPI_COMM_WORLD, &reqs1[1]);MPI_Wait(&reqs1[1],&status1);
		MPI_Isend(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD, &reqs1[0]);MPI_Wait(&reqs1[0],&status2);
	}

	for (i= 0; i < rounds; i++)
	{ 
	if (rank == 1 || 2)
		{
		MPI_Irecv(&token2, 1, MPI_INT, right, tag2, MPI_COMM_WORLD, &reqs2[0]);
		
		MPI_Wait(&reqs2[0],&status2);
		// MPI_Test(&reqs2[0], &flag2, &status2);
		// while (flag2 == 0) {
			// MPI_Test(&reqs2[0], &flag2, &status2);
		// }
		
		printf("Rank %3d: received token1 %2d from rank %3d. (counter clock-wise)\n", rank, token2, right);
		token2 = token2 - 1;
		
		//sleep(1); /* To see the output printed one by one simulating message passing */
		
		if (((rank != 0) || (i < (rounds - 1))) )
		{
			/* Only send it on if we are not rank 0, or therefsdf are more rounds to go */
			MPI_Isend(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD, &reqs1[0]);MPI_Wait(&reqs1[0],&status2);
		}
		
		
		MPI_Irecv(&token1, 1, MPI_INT, left, tag1, MPI_COMM_WORLD, &reqs2[1]);
		MPI_Wait(&reqs2[1],&status1);
		// MPI_Test(&reqs2[1], &flag1, &status1);
		// while (flag1 == 0) {
			// MPI_Test(&reqs2[1], &flag1, &status1);
		// }
		
		printf("Rank %3d: received token1 %2d from rank %3d. (clock-wise)\n", rank, token1, left);
		token1 = token1 + 1;
		
		//sleep(1); /* To see the output printed one by one simulating message passing */
		
		if (((rank != 0) || (i < (rounds - 1))) )
		{
			/* Only send it on if we are not rank 0, or there are more rounds to go */
			MPI_Isend(&token1, 1, MPI_INT, right, tag1, MPI_COMM_WORLD, &reqs1[1]);MPI_Wait(&reqs1[1],&status1);
		}
		}
		
		if (rank == 3) 
		{
		
		MPI_Irecv(&token1, 1, MPI_INT, left, tag1, MPI_COMM_WORLD, &reqs2[1]);
		MPI_Wait(&reqs2[1],&status1);
		// MPI_Test(&reqs2[1], &flag1, &status1);
		// while (flag1 == 0) {
			// MPI_Test(&reqs2[1], &flag1, &status1);
		// }
		
		printf("Rank %3d: received token1 %2d from rank %3d. (clock-wise)\n", rank, token1, left);
		token1 = token1 + 1;
		
		//sleep(1); /* To see the output printed one by one simulating message passing */
		
		if (((rank != 0) || (i < (rounds - 1))) )
		{
			/* Only send it on if we are not rank 0, or there are more rounds to go */
			MPI_Isend(&token1, 1, MPI_INT, right, tag1, MPI_COMM_WORLD, &reqs1[1]);MPI_Wait(&reqs1[1],&status1);
		}
		
		MPI_Irecv(&token2, 1, MPI_INT, right, tag2, MPI_COMM_WORLD, &reqs2[0]);
		
		MPI_Wait(&reqs2[0],&status2);
		// MPI_Test(&reqs2[0], &flag2, &status2);
		// while (flag2 == 0) {
			// MPI_Test(&reqs2[0], &flag2, &status2);
		// }
		
		printf("Rank %3d: received token1 %2d from rank %3d. (counter clock-wise)\n", rank, token2, right);
		token2 = token2 - 1;
		
		//sleep(1); /* To see the output printed one by one simulating message passing */
		
		if (((rank != 0) || (i < (rounds - 1))) )
		{
			/* Only send it on if we are not rank 0, or therefsdf are more rounds to go */
			MPI_Isend(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD, &reqs1[0]);MPI_Wait(&reqs1[0],&status2);
		}
		
		
		
		}
	}
	
	MPI_Finalize();
	return 0;
}


