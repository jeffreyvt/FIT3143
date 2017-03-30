#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int rc,rank, size, dest, source, input, tag=1;
	
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		scanf("%d", &input);
		printf("Process %d received %d from the input\n", rank, input);
		fflush(stdout);
		dest = 1;
		rc = MPI_Send(&input, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
	}
	else {
		rc = MPI_Recv(&input, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &Stat);
		printf("Process %d received %d from process %d with tag %d\n", rank, input, Stat.MPI_SOURCE, Stat.MPI_TAG);
		fflush(stdout);
		if (rank != size-1){
			rc = MPI_Send(&input, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
		}
	}
	
	MPI_Finalize();

	return 0;



}
