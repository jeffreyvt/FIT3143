#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int rc, rank, size, tag = 1, dest, source, message;
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
		for (int i = 0; i < 100 * (size-1); i = i + 1){
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,MPI_COMM_WORLD, &Stat);
		printf("rank 0 received a message from rank %d\n", message);
		fflush(stdout);
		}	
	}
	else {
		for (int i = 0; i < 100; i = i + 1){
			message = rank;
			MPI_Send(&rank, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);	
		}		
	}







	MPI_Finalize();
	return 0;

}
