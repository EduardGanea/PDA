#include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>

int prime_number(int n, int id, int p);

int main(int argc, char* argv[])
{
	int id;
	int ierr;
	int n;
	int n_factor;
	int n_hi;
	int n_lo;
	int p;
	int primes;
	int primes_part;
	double wtime;

	n_lo = 1;
	n_hi = 15;
	n_factor = 2;
	/*
	  Initialize MPI.
	*/
	ierr = MPI_Init(&argc, &argv);

	if (ierr != 0)
	{
		printf("\n");
		printf("MPI error\n");
		exit(1);
	}
	/*
	  Get the number of processes.
	*/
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &p);
	/*
	  Determine this processes's rank.
	*/
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);

	if (id == 0)
	{
		printf("\n");
		printf("PRIME_MPI\n");
		printf("  C/MPI version\n");
		printf("\n");
		printf("  An MPI example program to count the number of primes.\n");
		printf("  The number of processes is %d\n", p);
		printf("\n");
		printf("         N        Pi          Time\n");
		printf("\n");
	}

	n = n_lo;

	while (n <= n_hi)
	{
		ierr = MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

		primes_part = prime_number(n, id, p);

		ierr = MPI_Reduce(&primes_part, &primes, 1, MPI_INT, MPI_SUM, 0,
			MPI_COMM_WORLD);

		if (id == 0)
		{
			printf("  %8d  %8d\n", n, primes);
		}
		n = n +1;
	}
	/*
	  Terminate MPI.
	*/
	ierr = MPI_Finalize();
	/*
	  Terminate.
	*/

	return 0;
}
/******************************************************************************/

int prime_number(int n, int id, int p, int pr[100])

{
	int i;
	int j;
	int prime;
	int total;

	total = 0;

	for (i = 2 + id; i <= n; i = i + p)
	{
		prime = 1;
		for (j = 2; j < i; j++)
		{
			if ((i % j) == 0)
			{
				prime = 0;
				break;
			}
		}
		total = total + prime;
	}
	return total;
}
/******************************************************************************/
