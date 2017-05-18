#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
	int rank, size, dest, source, input, tag=1;
	char *array, *target;
	char *array_p, *target_p;
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double time;
	double start, end;
	int extra = 4096;
	for (int i = 1; size < 1000000; size *= 2) {
		array = array_p = (char *) malloc(i*sizeof(int) + extra);
		target = target_p = (char *)malloc(i*sizeof(int) + extra);
		printf("memory allocated\n");
		fflush(stdout);
		
		//unaligning
		target_p += 7;
		array_p += 10;
		if ((((long)target_p)&0x3) == (((long)array_p)&0x3)){
			target_p += 3;
		}
		time = 9999.9;
		for (int j=0; j<10; j++){
			start = MPI_Wtime();
			memcpy(target_p, array_p, size*sizeof(int));
			end = MPI_Wtime();
			
			if ((end-start)<time) time = end-start;
		}
		free(array);
		free(target);
		printf("size:%d time:%f", size, time);
		fflush(stdout);
		
	}
	
	MPI_Finalize();
	return 0;


}
