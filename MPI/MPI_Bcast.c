/*
 * File: MPI_Bcast.c
 *
 * Compile: mpicc -g -Wall -o MPI_Bcast MPI_Bcast.c
 * Run: mpiexec -n <np> ./MPI_Bcast
 *
 ************************************************************************************
 * Broadcasts a message from the process with rank root to all other processes of the group.
 *
 * int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
 *                      int root, MPI_Comm comm)
 *
 *
 */

#include <stdio.h>
#include <mpi.h>

 int main(void) {

     int my_rank;
     int world_size;

     int a;

     MPI_Init(NULL, NULL);
     MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
     MPI_Comm_size(MPI_COMM_WORLD, &world_size);

     if(my_rank == 0) {
         printf("Enter a\n");
         scanf("%d", &a);

     }
     //MPI_Barrier(MPI_COMM_WORLD);
     MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);

     printf("rank%d, a = %d\n", my_rank, a);

     MPI_Finalize();
     return 0;
 }
