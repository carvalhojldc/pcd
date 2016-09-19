/* File:
 *    mpi_tree.c
 *
 * Multiple cores forming a global sum -> with MPI
 *
 * Compile:
 *    mpicc -g -Wall -o mpi_tree mpi_tree.c
 * Usage:
 *    mpiexec -n <number of processes> ./mpi_tree
 */

#include <stdio.h>
#include <mpi.h>

int main() {

	int divisor = 2;
	int core_difference = 1;
	int core_send;
	int core_recv;
	int control = 1;

	int sum = 0;
	int sum_aux = 0;

	int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	sum = my_rank;

	/* Para o exemplo do livro */
	switch (my_rank) {
		case 0:
			sum = 8;
		break;
		case 1:
			sum = 19;
		break;
		case 2:
			sum = 7;
		break;
		case 3:
			sum = 15;
		break;
		case 4:
			sum = 7;
		break;
		case 5:
			sum = 13;
		break;
		case 6:
			sum = 12;
		break;
		case 7:
			sum = 14;
		break;
	}

	while(my_rank%control == 0 && control<comm_sz) {
		if(my_rank % divisor == 0) {
			core_recv = my_rank + core_difference;
			MPI_Recv(&sum_aux, 1, MPI_INT, core_recv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += sum_aux;
			printf("+ Sou %d, recebi %d de %d, tenho %d\n", my_rank, sum_aux, core_recv, sum);
		} else {
			core_send = my_rank - core_difference;
			MPI_Send(&sum, 1, MPI_INT, core_send, 0, MPI_COMM_WORLD);
			printf("- Sou %d e enviei %d para %d\n", my_rank, sum, core_send);
		}

		control *= 2;
		divisor *= 2;
		core_difference *= 2;
	}
	printf("### Sou %d e terminei meu trabalho, adeus\n", my_rank);

	if(my_rank == 0) {
		printf("A soma total foi = %d\n", sum);
	}

    MPI_Finalize();

	return 0;
}
