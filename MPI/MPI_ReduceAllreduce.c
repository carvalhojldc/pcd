/*
 * File: MPI_ReduceAllreduce.c
 *
 * Compile: mpicc -g -Wall -o MPI_ReduceAllreduce MPI_ReduceAllreduce.c
 * Run: mpiexec -n <np> ./MPI_ReduceAllreduce
 *
 ***************************************************************************************
 * Reduces values on all processes within a group.
 *
 * int MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
 *               MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
 *
 * https://www.open-mpi.org/doc/current/man3/MPI_Reduce.3.php
 * *************************************************************************************
 * Combines values from all processes and distributes the result back to all processes.
 *
 * int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
 *           MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
 *
 * https://www.open-mpi.org/doc/current/man3/MPI_Allreduce.3.php
 * *************************************************************************************
 *
 * Output:
 * 		mpiexec -n 4 ./MPI_Allreduce
 *             Reduce rank0, sum = -1
 *             Reduce rank3, sum = -1
 *             Reduce rank1, sum = -1
 *             Reduce rank2, sum = 6
 *             Allreduce rank0: sum = 6
 *             Allreduce rank2: sum = 6
 *             Allreduce rank3: sum = 6
 *             Allreduce rank1: sum = 6
 *
 *
 */

#include <stdio.h>
#include <mpi.h>

int* getArray(int num_elements);

int main(void) {

	int my_rank;
    int comm_sz;

    int sum;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    sum = -1;

    /* Reduce */
    MPI_Reduce(&my_rank, &sum, 1, MPI_INT, MPI_SUM, 2, MPI_COMM_WORLD); /* for rank 2*/
    printf("Reduce rank%d, sum = %d\n", my_rank, sum);

    /* Allreduce */
	MPI_Allreduce(&my_rank, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	printf("Allreduce rank%d: sum = %d\n", my_rank, sum);

	MPI_Finalize();
	return 0;
}
