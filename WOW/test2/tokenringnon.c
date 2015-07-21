#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, nprocs;
	int i, token1, token2, tag1 = 11, tag2 = 22, rounds, flag1, flag2, flag_p1 = 0;
	int left, right;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Status status1[2], status2[2];
	MPI_Request reqs1, reqs2;
	
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
		MPI_Isend(&token1, 1, MPI_INT, right, tag1, MPI_COMM_WORLD, &reqs1);
		MPI_Isend(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD, &reqs2);
	}

	for (i= 0; i < rounds; i++)
	{
		MPI_Irecv(&token1, 1, MPI_INT, left, tag1, MPI_COMM_WORLD, &reqs1);
		MPI_Wait(&reqs1,status1);
		
		MPI_Irecv(&token2, 1, MPI_INT, right, tag2, MPI_COMM_WORLD, &reqs2);
		
		//MPI_Test(&reqs1, &flag2, status1);
		MPI_Test(&reqs2, &flag2, status2);
		
		// while (!flag1 || !flag2) {
			// MPI_Test(&reqs1, &flag2, status1);
			// MPI_Test(&reqs2, &flag2, status2);
		// }
		
			
			
		
		// while(!flag2)
		// {
			// //MPI_Irecv(&token2, 1, MPI_INT, right, tag2, MPI_COMM_WORLD, &reqs2);
			// MPI_Test(&reqs2, &flag2, status2);
		// }
		
		//printf("MPI source 1: %3d.  source 2: %3d.  flag: %3d and %3d. tag: %3d and %3d.\n", status1->MPI_SOURCE, status2->MPI_SOURCE, flag1, flag2, status1->MPI_TAG, status2->MPI_TAG);
		
		
		sleep(1); /* To see the output printed one by one simulating message passing */
		
		if (((rank != 0) || (i < (rounds - 1))) && flag1)
		{
			printf("Rank %3d: received token1 %2d from rank %3d. (clock-wise)\n", rank, token1, left);
			token1 = token1 + 1;
			/* Only send it on if we are not rank 0, or there are more rounds to go */
			MPI_Isend(&token1, 1, MPI_INT, right, tag1, MPI_COMM_WORLD, &reqs1);
			while(!flag_p1) {
				MPI_Iprobe(rank, tag1, MPI_COMM_WORLD, &flag_p1, status1);
			}
		}
		
		if (((rank != 0) || (i < (rounds - 1))) && flag2)
		{		
			printf("Rank %3d: received token2 %2d from rank %3d. (counter clock-wise)\n", rank, token2, right);
			token2 = token2 - 1;
			/* Only send it on if we are not rank 0, or there are more rounds to go */
			MPI_Isend(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD, &reqs2);
		}
		
	}
	
	MPI_Finalize();
	return 0;
}

/*

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int numtasks, rank, next, prev, buf[2], tag1=1, tag2=2;
	to

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	prev = rank-1;
	next = rank+1;
	if (rank == 0)  prev = numtasks - 1;
	if (rank == (numtasks - 1))  next = 0;
	
	next = (rank + 1) % numtasks;
    prev = (numtasks + rank - 1) % numtasks;
	
	MPI_Irecv(&rank, 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
	//MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);

	//MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[1]);

	MPI_Waitall(2, reqs, stats);
	printf("Rank %3d: received token %3d from rank %3d.\n",rank,rank,prev);
	sleep(1);

	MPI_Finalize();
	}

*/
