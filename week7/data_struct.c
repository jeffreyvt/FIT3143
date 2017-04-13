#include <stdio.h>
#include "mpi.h"
#include <float.h>

int main (int argc, char *argv[]){
	int rc, rank, size, dest,maxn, source, tag=1;
		
	
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	

	if (rank == 0) {
		scanf("%d", &maxn);
		printf("maxn = %d\n", maxn);
		fflush(stdout);
		
		
	}
	MPI_Bcast(&maxn, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	double xlocal[(maxn/size)+2][maxn];
	if (rank == 0) {
		double x[maxn][maxn];
		int count = 1;
		for (int i = 0; i < maxn; i = i + 1){
			for (int j = 0; j < maxn; j = j + 1){
				x[i][j] = count;
				count = count + 1;
			}
		}
		/* //this is for printing out the array
		for (int i = 0; i < maxn; i++) {
			for (int j = 0; j < maxn; j++) {
				printf("%f ", x[i][j]);
			}
			printf("\n");
		}
		*/

		//process all the ones after the rank 0 first
		int receiver_rank = 1;
		for (int k = maxn/size; k < maxn - (maxn/size); k = k + maxn/size ) {
			int li = 0;
			for (int i = k-1; i < k + (maxn/size)+1; i++) {
				for (int j = 0; j < maxn; j++)	{
					xlocal[li][j] = x[i][j];		
				}
				li = li + 1;
			}
			MPI_Send(&xlocal, (maxn/size + 2)*maxn, MPI_DOUBLE, receiver_rank, tag, MPI_COMM_WORLD);
			receiver_rank = receiver_rank + 1;
		}
		//process the last row to have last ghost variable to be DBL_MAX
		int i = maxn-(maxn/size)-1;
		int li = 0;
		for (i; i < maxn; i++){
			for (int j = 0; j < maxn; j++) {
				xlocal[li][j] = x[i][j];
			}
			li = li + 1;	
		}
		for (int j = 0; j < maxn; j++) {
			xlocal[(maxn/size) + 1][j] = DBL_MAX;
		}
		MPI_Send(&xlocal, (maxn/size + 2)*maxn, MPI_DOUBLE, size-1, tag, MPI_COMM_WORLD);
		
		//process the first row
		for (int i = 0; i < maxn/size +2; i++){
			if ( i == 0){
				for (int j = 0; j < maxn; j++){
					xlocal[i][j] = DBL_MAX;
				}
			}
			else{
				for (int j = 0; j < maxn; j++){
					xlocal[i][j] = x[i-1][j];
				}
			}
		}
	}
	else {
		MPI_Recv(&xlocal, (maxn/size + 2)*maxn, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &Stat);
	}


	
	//The next step prints out all the ghost and the values of the processes sequentially
	int flag = 0;
	if (rank == 0) {
		flag = 1;
		printf("This is process rank = %d, and its values as follows:\n", rank);
		for (int i = 0; i < maxn/size + 2; i++) {
			for (int j = 0; j < maxn; j++) {
				printf("%f ", xlocal[i][j]);
			}
			printf("\n");
		}
		MPI_Send(&flag, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);	
	}
	else if (rank != 0) {
		MPI_Recv(&flag, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &Stat);
		printf("This is process rank = %d, and its values as follows:\n", rank);
		for (int i = 0; i < maxn/size + 2; i++) {
			for (int j = 0; j < maxn; j++) {
				printf("%f ", xlocal[i][j]);
			}
			printf("\n");
		}
		if (rank < size-1) {
			MPI_Send(&flag, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
		}
		
	}
	printf("the size is=%d", size);
	fflush(stdout);

	MPI_Finalize();
	return 0;


}
