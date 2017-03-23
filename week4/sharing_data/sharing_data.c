#include <stdio.h>
#include "mpi.h"
#include <unistd.h>

int main(argc,argv)
int argc;
char **argv;

{
	int rank, size;
	int input;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	do{
		if (rank == 0)
			{
                                printf("\nEnter Value: ");
				fflush(stdout);
				scanf("%d", &input);
			}
		MPI_Bcast(&input, 1, MPI_INT, 0, MPI_COMM_WORLD);
		printf("This is process %d, value: %d\n", rank, input);
		fflush(stdout);
		usleep(200);
	} while (input >= 0);
	
	if (rank == 0) {printf("A negative number has been detected, the program exits\n");}
	MPI_Finalize();
	return 0;

}
