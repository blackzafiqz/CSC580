#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int masin(int argc, char** argv)
{
	int rank, size;
	int apple[10] = { 86, 43, 68, 52, 58, 67, 89, 89, 94, 68 };
	int samsung[10] = { 97, 37, 100, 11, 52, 96, 10, 58, 47, 42 };
	int oppo[10] = { 11, 70, 98, 60, 72, 57, 34, 42, 63, 57 };
	int* brands[3] = { apple,samsung,oppo };
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //find out rank number
	MPI_Comm_size(MPI_COMM_WORLD, &size); //find how many processes were started.
	//display the value for each array
	for (int arr = 0; arr < size; arr++)
	{
		for (int rank = arr; rank < 3; rank++)
		{
			if (rank == 0)
				printf("Rank %d for Brand %d (Apple) has sales of :", rank, rank
					+ 1);
			if (rank == 1)
				printf("Rank %d for Brand %d (Samsung) has sales of :", rank, rank
					+ 1);
			if (rank == 2)
				printf("Rank %d for Brand %d (Oppo) has sales of :", rank, rank
					+ 1);
			for (int j = 0; j < 10; j++)
			{
				if (rank == 0)
					printf(" %d ", apple[j]);
				if (rank == 1)
					printf(" %d ", samsung[j]);
				if (rank == 2)
					printf(" %d ", oppo[j]);
			}
			printf("\n");
			//find minimum sales for each brand
			int localmin[2];
			int globalmin[2];
			localmin[0] = brands[rank][0];
			for (int i = 0; i < 10; i++)
				if (brands[rank][i] < localmin[0])
					localmin[0] = brands[rank][i];
			localmin[1] = rank;
			// Reduce all of the local minimum value into the global minimum value in order to
			// display minimum sales for each brand..
			MPI_Allreduce(localmin, globalmin, 1, MPI_2INT, MPI_MINLOC,
				MPI_COMM_WORLD);
			printf("Rank %d lowest sales is %d thousand units\n", globalmin[1],
				globalmin[0]);
			//find maximum sales for each brand
			int localmax[2];
			int globalmax[2];
			localmax[0] = brands[rank][0];
			for (int i = 0; i < 10; i++)
				if (brands[rank][i] > localmax[0])
					localmax[0] = brands[rank][i];
			localmax[1] = rank;
			// Reduce all of the local maximum value into the global maximum value in order to
				// display maximum sales for each brand
			MPI_Allreduce(localmax, globalmax, 1, MPI_2INT, MPI_MAXLOC, MPI_COMM_WORLD);
			printf("Rank %d highest sales is %d thousand units\n", globalmax[1],
				globalmax[0]);
			printf("\n");
		}
	}
	printf("The minimum and maximum sales for all three brands : \n");
	//find minimum sales for all brands
	int localmin[2];
	int globalmin[2];
	localmin[0] = brands[0][0];
	for (int rank = 0; rank < 3; rank++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (brands[rank][i] <= localmin[0])
			{
				localmin[0] = brands[rank][i];
				localmin[1] = rank;
			}
		}
	}
	// Reduce all of the local minimum value into the global minimum value in order to
	// display minimum sales for all brands
	MPI_Allreduce(localmin, globalmin, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);
	printf("Rank %d has the lowest sales (minimum) among three brands which is %d thousand units\n", globalmin[1], globalmin[0]);
	//find maximum sales for all elements in all brands
	int localmax[2];
	int globalmax[2];
	localmax[0] = brands[0][0];
	for (int rank = 0; rank < 3; rank++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (brands[rank][i] >= localmax[0])
			{
				localmax[0] = brands[rank][i];
				localmax[1] = rank;
			}
		}
	}
	// Reduce all of the local maximum value into the global maximum value in order to
	// display maximum sales for all brand.
	MPI_Allreduce(localmax, globalmax, 1, MPI_2INT, MPI_MAXLOC, MPI_COMM_WORLD);
	printf("Rank %d has highest sales (maximum) among three brands which is %d thousand units\n", globalmax[1], globalmax[0]);
	printf("\n");
	MPI_Finalize(); // performs various clean-up tasks to terminate the MPI environment.
	return 0;
}