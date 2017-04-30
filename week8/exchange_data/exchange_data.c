#include <stdio.h>
#include "mpi.h"

int main( int argc, char *argv[]) {
	int rank, size, dest, source;

	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	dest = rank + 1;
	if (dest > size-1) {
		dest = 0;
	}
	source = rank - 1;
	if (source < 0) {
		source = size-1;
	}

	int rec_val;
	MPI_Sendrecv(&rank, 1, MPI_INT, dest, 1,
				&rec_val, 1, MPI_INT, source, 1,
				MPI_COMM_WORLD, &Stat);
	printf("This is rank %d, I have received data from rank %d\n", rank, rec_val);

	MPI_Finalize();

	return 0;
}