/*
 * Compile: mpicc -g -Wall -o MPI_ScatterGather MPI_ScatterGather.c
 * Run: mpiexec -n <number of cores> ./MPI_ScatterGather
 *
 * MPI_Scatter: Sends data from one task to all tasks in a group.
 * 		int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
 *		    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
 *
 * MPI_Gather: Gathers values from a group of processes.
 *	 	int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
 *   		void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

//#define DEBUG

int* getArray(int num_elements);

int computeSum(int *array, int num_elements);

int main( int argc, char **argv ) {

	int my_rank;
	int comm_sz;
	int i;

	int data_sz;
	int data_send_sz;
	int *data = NULL;

	int local_sum;
	int *sum_all = NULL; /*for rank 0*/

    MPI_Init(NULL, NULL);
    MPI_Comm_rank( MPI_COMM_WORLD, &my_rank );
    MPI_Comm_size( MPI_COMM_WORLD, &comm_sz );

	data_send_sz = 3;
	data_sz = data_send_sz * comm_sz;

	data = malloc(sizeof(int)*data_sz);
    if(my_rank == 0){
		data = getArray(data_sz);
  		sum_all = malloc(sizeof(int)*comm_sz);
	}

	MPI_Scatter(data, data_send_sz, MPI_INT, data, data_send_sz, MPI_INT, 0, MPI_COMM_WORLD);

	local_sum = computeSum(data, data_send_sz);

    free(data);

	MPI_Gather(&local_sum, 1, MPI_INT, sum_all, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(my_rank == 0) {
		for(i=0; i<comm_sz; i++) {
			printf("sum rank%d = %d\n", i, sum_all[i]);
		}
		free(sum_all);

	}

    MPI_Finalize();
    return 0;
}

int* getArray(int num_elements) {
	int *array = (int*)malloc(sizeof(int)*num_elements);
	int i;

	for(i = 0; i < num_elements; i++) {
		array[i] = i;
		#ifdef DEBUG
		printf("array[%d] = %d\n", array[i], i);
		#endif
	}

	return array;
}

int computeSum(int *array, int num_elements) {
	int sum = 0;
	int i;

	for(i=0; i<num_elements; i++) {
		sum += array[i];
	}

	return sum;
}
