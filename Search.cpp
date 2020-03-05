# include <stdlib.h>
# include <stdio.h>
# include "mpi.h"

int main(int argc, char* argv[]);
int search(int a, int b, int c, int id, int p);

int main(int argc, char* argv[])
{
	int a;
	int b;
	int c;
	int i4_huge = 85;
	int id;
	int j;
	int p;
	double wtime;
	/*
	  Initialize MPI.
	*/
	MPI_Init(&argc, &argv);
	/*
	  Get this processor's ID.
	*/
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	/*
	  Get the number of processes.
	*/
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	a = 1;
	b = i4_huge;
	c = 45;

	if (id == 0)
	{
		printf("\n");
		printf("  Search the integers from A to B\n");
		printf("\n");
		printf("  A           = %d\n", a);
		printf("  B           = %d\n", b);
		printf("  C           = %d\n", c);
	}


	j = search(a, b, c, id, p);


	if (j != -1)
	{
		printf("\n");
		printf("  Process %d found     J = %d\n", id, j);
	}
	else {
		printf("Not found");
	}

	/*
	  Terminate MPI.
	*/
	MPI_Finalize();

	/*
	  Terminate.
	*/
	if (id == 0)
	{
		printf("\n");
		printf("SEARCH_MPI:\n");
		printf("  Normal end of execution.\n");
		printf("\n");
	}

	return 0;
}
/******************************************************************************/

int search(int a, int b, int c, int id, int p)

{
	int i;
	int j;

	j = -1;
	/*
	  i = i + p can take us "over top" so that i becomes negative!
	  So we have to be more careful here!
	*/
	for (i = a + id; 0 < i && i <= b; i = i + p)
	{

		if (i == c)
		{
			j = i;
			break;
		}
	}

	return j;
}
