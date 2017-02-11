#include <iostream>
#include <omp.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <stdio.h>


float a[400000000] ;

void quickSort(int num, float* a, int n) {
	long i = 0, j = n;
	float	pivot = a[n / 2];


	do {
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;

		if (i <= j) {
      std::swap(a[i], a[j]);
			i++; j--;
		}
	} while (i <= j);


	if (n < 400000000)
    {
		if (j > 0) quickSort(num * 2 + 1, a, j);
		if (n > i) quickSort(num * 2 + 2, a + i, n - i);
		//for (int i = 0; i<=n; i++)    {printf(" %f \n\n", a[i]);}printf(" ----------------------\n");
		return;
	}

#pragma omp task shared(a)
	{
		if (j > 0) quickSort(num * 2 + 1, a, j);
		//for (int i = 0; i<=n; i++){ printf(" %f \n\n", a[i]);} printf(" ----------------------\n");
	}


#pragma omp task shared(a)
	{
		if (n > i) quickSort(num * 2 + 2, a + i, n - i);
		//for (int i = 0; i<=n; i++){printf(" %f \n\n", a[i]);} printf(" ----------------------\n");
	}


}
void init(int n)
{
//	time_t t;
//	srand(1);
time_t t;
srand((unsigned)time(&t));

	printf( "Array: \n");
	for (int i = 0; i<n; i++)
	{
		a[i] = 2*(rand() % 100)+1;
	}

    //for (int i = 0; i<n;i++){ printf(" %f ", a[i]);}printf( "\n\n");

	return ;
}


int main() {
	int n;
scanf("%d",&n);
	init(n);

#pragma omp parallel shared(a) num_threads(8)
	{
		#pragma omp single nowait
		{
		    double t0 = omp_get_wtime();
			quickSort(0, a, n - 1);
			double t1 = omp_get_wtime();
	printf("time for  core is  %.3f s \n", t1 - t0);
	printf (" threads number %d \n" ,omp_get_num_threads());

		    double t2 = omp_get_wtime();
			quickSort(0, a, n - 1);
			double t3 = omp_get_wtime();
	printf("time for  core is  %.3f s \n", t3 - t2);
	printf (" threads number %d \n" ,omp_get_num_threads());

		    double t4 = omp_get_wtime();
			quickSort(0, a, n - 1);
			double t5 = omp_get_wtime();
	printf("time for  core is  %.3f s \n", t5 - t4);
	printf (" threads number %d \n" ,omp_get_num_threads());

		    double t6 = omp_get_wtime();
			quickSort(0, a, n - 1);
			double t7 = omp_get_wtime();
	printf("time for  core is  %.3f s \n", t7 - t6);
	printf (" threads number %d \n" ,omp_get_num_threads());
		}
	}
  delete []a;
}
