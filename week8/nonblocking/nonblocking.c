#include <stdio.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int rc,rank, size, dest, source, input, tag=1;
	int a=0,b=0;
	
	MPI_Status Stat[2];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Request reqs[2];
/*
	if (rank == 0) {
		scanf("%d", &input);
		printf("Process %d received %d from the input\n", rank, input);
		fflush(stdout);
		dest = 1;
		rc = MPI_Isend(&input, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD,&re);
	}
	else {
		rc = MPI_Irecv(&input, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &Stat);
		printf("Process %d received %d from process %d with tag %d\n", rank, input, Stat.MPI_SOURCE, Stat.MPI_TAG);
		fflush(stdout);
		if (rank != size-1){
			rc = MPI_Isend(&input, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
		}
	}
*/
	if (rank == 1){
		input = 4;
		MPI_Isend(&input, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &reqs[0]);
	}
	else if (rank == 2){
		input = 5;
		MPI_Isend(&input, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &reqs[1]);
	}
	else if (rank == 0){
		MPI_Irecv(&a, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &reqs[0]);
		MPI_Irecv(&b, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &reqs[1]);
		MPI_Waitall(2, reqs, Stat);
		int c = a+b;
		printf("%d\n", c);
		fflush(stdout);
	}

	MPI_Finalize();

	return 0;
}
