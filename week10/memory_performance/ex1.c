#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
	int rank, size, dest, source, input, tag=1;
	int *array, *target;
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double time;
	double start, end;
	
	for (int i = 1; i < 100000000; i *= 2) {
		array = (int *)malloc(i*sizeof(int));
		target = (int *)malloc(i*sizeof (int));
		time = 9999.9;
		for (int j = 0; j < 10; j++) {
			start = MPI_Wtime();
			memcpy(array, target, i*sizeof(int));
			end = MPI_Wtime();
			if (end - start < time) {
				time = end-start;			
			}
		}
		free(array);
		free(target);
		printf("%d of integers, copying took %f, speed is %f MB/s\n", i, time, i*4/time/1000000);
		fflush(stdout);
		
	}

	//printf("the time it took for rank: %d is %f seconds\n", rank, end-start);
	MPI_Finalize();
	return 0;


}
