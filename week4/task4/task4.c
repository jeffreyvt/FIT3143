#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int rank, packsize;
	struct {int a; double b;} value;
	MPI_Datatype mystruct;
	int blocklens[2];
	char packbuff[100];
	int position;
	MPI_Aint indices[2];
	MPI_Datatype old_types[2];

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// one value of each type
	blocklens[0] = 1;
	blocklens[1] = 1;
	// The base types
	old_types[0] = MPI_INT;
	old_types[1] = MPI_DOUBLE;
	// the location of each element
	MPI_Address(&value.a, &indices[0]);
	MPI_Address(&value.b, &indices[1]);
	// Make relative
	indices[1] = indices[1] - indices[0];
	indices[0] = 0;
	MPI_Type_struct(2, blocklens, indices, old_types, &mystruct);

	MPI_Type_commit(&mystruct);

	do
	{
		position = 0;
		if (rank == 0)
		{
			packsize = 0;
			scanf("%d%lf", &value.a, &value.b);
			MPI_Pack(&value, 1, mystruct, packbuff, 100, &packsize, MPI_COMM_WORLD);
		}
		MPI_Bcast(&packsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(packbuff, packsize, MPI_PACKED, 0, MPI_COMM_WORLD);
		if (rank != 0)
		{
			MPI_Unpack(packbuff, packsize, &position, &value, 1, mystruct, MPI_COMM_WORLD);		
		}		
		printf("Process %d got %d and %lf\n", rank, value.a, value.b);
	} while (value.a >= 0);

	MPI_Type_free(&mystruct);
	MPI_Finalize();
	return 0;

}
