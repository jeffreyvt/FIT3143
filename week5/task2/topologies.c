#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int rc,rank, size,junk, dest, scanfout, source, input, tag=1, false = 0;
	
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Comm comm;

	MPI_Cart_create(MPI_COMM_WORLD, 1, &size, &false, 0, &comm);
	MPI_Cart_shift(comm, 0, 1, &source, &dest);
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);
	
	
	if (rank == 0) {
		scanfout = scanf("%d", &input);
		if (scanfout == 1){
			printf("Process %d received %d from the input\n", rank, input);
			fflush(stdout);
			//MPI_Cart_shift(comm, 0, 1, &junk, &source);
			rc = MPI_Send(&input, 1, MPI_INT, dest, tag, comm);
		}
		else {printf("scanf failed, we are expecting an integer!!!!!\n");return 0;}
	}
	else {
		//MPI_Cart_shift(comm, 1, 1, &junk, &source);
		//MPI_Cart_shift(comm, 1, -1, &junk, &source);
		rc = MPI_Recv(&input, 1, MPI_INT, source, tag, comm, &Stat);
		printf("Process %d received %d from process %d with tag %d\n", rank, input, Stat.MPI_SOURCE, Stat.MPI_TAG);
		fflush(stdout);
		if (rank != size-1){
			rc = MPI_Send(&input, 1, MPI_INT, dest, tag, comm);
		}
	}
	
	MPI_Finalize();

	return 0;



}
