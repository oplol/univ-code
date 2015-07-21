#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
int numtasks, rank, next, prev, buf[2], tag1=1, tag2=2;
MPI_Request reqs[4];
MPI_Status stats[2];

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

buf[0] = 0;
buf[1] = numtasks;

prev = rank-1;
next = rank+1;
if (rank == 0)  prev = numtasks - 1;
if (rank == (numtasks - 1))  next = 0;

MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);
buf[0]++;

MPI_Isend(&buf[1], 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
MPI_Isend(&buf[0], 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);

//MPI_Wait( reqs, stats);
//printf("Task %d communicated with tasks %d & %d\n",rank,prev,next);
printf("Rank %3d: received token1 %2d from rank %3d. (clock-wise)\n", rank, buf[0], prev);
printf("Rank %3d: received token2 %2d from rank %3d. (counter clock-wise)\n", rank, buf[1], next);
MPI_Waitall(4, reqs, stats);
MPI_Finalize();
}

