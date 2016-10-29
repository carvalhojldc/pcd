/*
 * File: MPI_Allgather.c
 *
 * Compile: mpicc -g -Wall -o MPI_Allgather MPI_Allgather.c
 * Run: mpiexec -n <np> ./MPI_Allgather
 *
 ************************************************************************************
 * Gathers data from all processes and distributes it to all processes
 *
 * int MPI_Allgather(const void *sendbuf, int  sendcount,
 *                   MPI_Datatype sendtype, void *recvbuf, int recvcount,
 *                   MPI_Datatype recvtype, MPI_Comm comm)
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void) {

    int my_rank;
    int comm_sz;
    int i;
    int *data = NULL;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    data = malloc(sizeof(int)*comm_sz);

    MPI_Allgather(&my_rank, 1, MPI_INT, data, 1, MPI_INT, MPI_COMM_WORLD);

    for(i = 0; i<comm_sz; i++) {
        printf("rank%d array[%d] = %d\n", my_rank, i, data[i]);
    }

    free(data);
    MPI_Finalize();
    return 0;
}
