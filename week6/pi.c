#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int rc, rank, size, dest, source, tag=1;
	float input;
	float recv_value = 0;
	float send_value = 0;
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0){
		scanf("%f", &input);
		printf("n is %f\n", input);
		fflush(stdout);
	}
	MPI_Bcast(&input, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	
	if (rank != 0){
		float i = 0;
		float x = 0;
		while (i < input/(size-1)){
			x = ((rank-1)+i*(size-1));
			//printf("x was:%f\n", x);
			//fflush(stdout);
			x = x/input;
			//printf("rank:%d x:%f input:%f size:%d i:%f\n", rank, x, input, size, i);
			//fflush(stdout);
			send_value = send_value + (1/input)*4/(1+x*x);
			i = i +1;
		}
	}
	int flag = 0;
	if (rank == 1){
		flag = 1;
		MPI_Send(&flag, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);	
	}
	else if (rank != 0) {
		MPI_Recv(&flag, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &Stat);
		if (rank != size-1){
			MPI_Send(&flag, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
		}
		else {
			MPI_Send(&flag, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);		
		}
	}
	if (rank == 0){
		MPI_Recv(&flag, 1, MPI_INT, size-1, tag, MPI_COMM_WORLD, &Stat);	
	}
	
	MPI_Reduce(&send_value, &recv_value, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0){
		printf("The value of pi is: %f\n", recv_value);
		fflush(stdout);
	}
	
	MPI_Finalize();

	return 0;
}
