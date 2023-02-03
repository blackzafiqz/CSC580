#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
//constant value
#define N 10
#define BRANDSIZE 3
int main(int argc, char* argv[])
{
	/*initialization*/
	int nthreads, tid, i, j, size, arr;
	/*array of sales*/
	int apple[] = { 86, 43, 68, 52, 58, 67, 89, 89, 94, 68 };
	int samsung[] = { 97, 37, 100, 11, 52, 96, 10, 58, 47, 42 };
	int oppo[] = { 11, 70, 98, 60, 72, 57, 34, 42, 63, 57 };
	int* brands[] = { apple,samsung,oppo };
	/*initialization for minimum maximum sales for each brand*/
	int minM = apple[0];
	int maxM = apple[0];
	int minL = samsung[0];
	int maxL = samsung[0];
	int minW = oppo[0];
	int maxW = oppo[0];
	int allMin = apple[0];
	int allMax = apple[0];
	arr = BRANDSIZE;
#pragma omp parallel shared(apple,samsung,oppo,nthreads) private(i,j,tid) num_threads(3)
	{
		//only 3 threads were used in this coding
		tid = omp_get_thread_num();
		if (tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
		printf("Thread %d starting...\n", tid);
#pragma omp for //for loop (for each brand maximum and minimum sales)
		for (i = 0; i < N; i++)
		{
			if (apple[i] < minM)
				minM = apple[i];
			printf("Thread %d: Minimum Sales for Apple = %d\n", tid, minM);
			if (samsung[i] < minL)
				minL = samsung[i];
			printf("Thread %d: Minimum Sales for Samsung = %d\n", tid, minL);
			if (oppo[i] < minW)
				minW = oppo[i];
			printf("Thread %d: Minimum Sales for Oppo = %d\n", tid, minW);
			if (apple[i] > maxM)
				maxM = apple[i];
			printf("Thread %d: Maximum Sales for Apple = %d\n", tid, maxM);
			if (samsung[i] > maxL)
				maxL = samsung[i];
			printf("Thread %d: Maximum Sales for Samsung = %d\n", tid, maxL);
			if (oppo[i] > maxW)
				maxW = oppo[i];
			printf("Thread %d: Maximum Sales for Oppo = %d\n", tid, maxW);
		}
#pragma omp for //for loop for all brands maximum and minimum sales
		for (i = 0; i < arr; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (brands[i][j] <= allMin)
					allMin = brands[i][j];
				printf("Thread %d: Minimum Sales for all brands= %d\n", tid,
					allMin);
				if (brands[i][j] >= allMax)
					allMax = brands[i][j];
				printf("Thread %d: Maximum Sales for all brands= %d\n", tid,
					allMax);
			}
		}
	} /* end of parallel section */
	//print all output
	printf("\n");
	printf("MINIMUM SALES FOR EACH BRANDS\n");
	printf("Minimum Sales for Apple : %d\n", minM);
	printf("Minimum Sales for Samsung : %d\n", minL);
	printf("Minimum Sales for Oppo : %d\n", minW);
	printf("\n");
	printf("MAXIMUM SALES FOR EACH BRANDS\n");
	printf("Maximum Sales for Apple : %d\n", maxM);
	printf("Maximum Sales for Samsung : %d\n", maxL);
	printf("Maximum Sales for Oppo : %d\n", maxW);
	printf("\n");
	printf("MINIMUM AND MAXIMUM SALES FOR ALL BRANDS\n");
	printf("Minimum Sales for all brands : %d\n", allMin);
	printf("Maximum Sales for all brands : %d\n", allMax);
}