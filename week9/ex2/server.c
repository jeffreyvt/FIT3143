#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
	int rc, rank, color, size, dest, source, input, tag=1;


	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) { //color 0 is master
		color = 0;
	}
	else { //color = 1 are slaves
		color = 1;
	}
	
	MPI_Comm Masters_and_slaves;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &Masters_and_slaves);
	
	int group_rank, group_size;
	MPI_Comm_rank(Masters_and_slaves, &group_rank);
	MPI_Comm_size(Masters_and_slaves, &group_size);
	//printf("world rank = %d, world size = %d, group rank = %d, group size = %d\n", rank, size, group_rank, group_size);
	//fflush(stdout);

	if (rank == 0) {
                for (int i = 0; i<size-1; i = i + 1){
			//printf("tries to receive %d\n", i);
                        char message[256];
                        MPI_Recv(&message, 256, MPI_CHAR, i+1, 1, MPI_COMM_WORLD, &Stat);
			printf("I have received a message from rank %d, and the message is: %s\n", Stat.MPI_SOURCE, message);
			fflush(stdout);
                        MPI_Recv(&message, 256, MPI_CHAR, i+1, 1, MPI_COMM_WORLD, &Stat);
			printf("I have received a message from rank %d, and the message is: %s\n", Stat.MPI_SOURCE, message);
			fflush(stdout);
                }
        }
	else {
		if (group_rank == 0) {
			char message[256];
			snprintf(message, sizeof(message), "Hello from slave %d", group_rank);
			MPI_Send(&message, 256, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
			snprintf(message, sizeof(message), "goodbye from slave %d", group_rank);
			MPI_Send(&message, 256, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
			
			if (group_size > 1) {
				int flag = 1;
				MPI_Send(&flag, 1, MPI_INT, group_rank + 1, 1, Masters_and_slaves);
			}
		}
		else {
			int flag;
			MPI_Recv(&flag, 1, MPI_INT, group_rank - 1, 1, Masters_and_slaves, &Stat);
			char message[256];
			snprintf(message, sizeof(message), "Hello from slave %d", group_rank);
			MPI_Send(&message, 256, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
			snprintf(message, sizeof(message), "goodbye from slave %d", group_rank);
			MPI_Send(&message, 256, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
			
			if (group_size > group_rank + 1) {
				flag = 1;
				MPI_Send(&flag, 1, MPI_INT, group_rank + 1, 1, Masters_and_slaves);
				//printf("%d\n", group_rank + 1);
			}
					
		}
		
	}
	
	char message[256];
	if (rank == 0) {
		int exits = 0;
		while(1) {
			if (exits == size-1){
				break;	
			}
			else {
				MPI_Recv(&message, 256, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &Stat);
				printf("I have received a message from rank %d, and the message is: %s\n", Stat.MPI_SOURCE, message);
				
				exits += 1;
			}
		}
	}
	else {
		snprintf(message, sizeof(message), "I'm exiting (%d)", group_rank);
		MPI_Send(&message, 256, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
	}
	fflush(stdout);


	MPI_Comm_free(&Masters_and_slaves);
	MPI_Finalize();	


	return 0;



}
