#include <stdio.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int rc,rank, size, dest, source, input, tag=1;
	int a=0,b=0;
	
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Request reqs[2];
	
	if (rank == 0) {
		a = 10;	
		printf("1This is rank: 0, I have a = %d, b = %d \n", a, b);
		fflush(stdout);
		dest = 1;
	}
	if (rank == 1) {
		b = 5;
		printf("1This is rank: 1, I have a = %d, b = %d \n", a, b);
		fflush(stdout);
		dest = 0;
		
	}
	MPI_Sendrecv(&b, 1, MPI_INT, dest, tag, &b, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &Stat);
	


	if (rank == 0) {
		
		printf("2This is rank: 0, I have a = %d, b = %d \n", a, b);
		fflush(stdout);
	}
	MPI_Sendrecv(&a, 1, MPI_INT, dest, tag, &a, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &Stat);
	if (rank == 1) {
		
		printf("2This is rank: 1, I have a = %d, b = %d \n", a, b);
		fflush(stdout);
	}

	MPI_Finalize();

	return 0;
}
