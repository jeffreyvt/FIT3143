#include <stdio.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int rc,rank, size, dest, source, input, tag=1;
	int value, rec_val;
	
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Request reqs[2];
	value = rank*2+100;
	printf("This is rank: %d it has its own value of %d\n", rank, value);
	fflush(stdout);
	if (rank == 0) {
		dest = 1;
	}
	else {
		dest = 0;
	}
	
	MPI_Sendrecv(&value, 1, MPI_INT, dest, tag, 
				&rec_val, 1, MPI_INT, dest, tag, 
				MPI_COMM_WORLD, &Stat);


		
	printf("This is rank: %d, I have val = %d, rec_val = %d \n", rank, value, rec_val);
	fflush(stdout);
	//MPI_Sendrecv(&a, 1, MPI_INT, dest, tag, &a, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &Stat);
/*
	if (rank == 1) {
		
		printf("2This is rank: 1, I have a = %d, b = %d \n", a, b);
		fflush(stdout);
	}
*/
	MPI_Finalize();

	return 0;
}
