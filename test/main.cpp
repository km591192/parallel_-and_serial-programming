#include <iostream>
#include <omp.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <ctime>
#include <time.h>

using namespace std;
int a[200000000];

//последовательное
int sum_arrpos(int *a, int n)
{
	int sum = 1;
	double t0 = omp_get_wtime();
	for (int i = 0; i < n; ++i)
		sum *= a[i];
	double t1 = omp_get_wtime();
	printf("time for 1 core is  %.3f s \n", t1 - t0);
	//printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
    //printf("num threads = %d\n" , omp_get_num_threads());
    printf( "sum  = %d\n" , sum );
	return sum;
}

//парарлельное на 1 потоке
int sum_arrparal1(int *a, const int n)
{
	int sum = 1;

	//omp_set_dynamic(0);
	omp_set_num_threads(1);

	double t0 = omp_get_wtime();

#pragma omp parallel shared(a) reduction (+: sum) //num_threads(1)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
			sum *= a[i];
		//cout << "sum thread  = " << sum << endl;
}
double t1 = omp_get_wtime();
	printf("time for 1 core is  %.3f s \n", t1 - t0);
	//printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
//printf("num threads = %d\n" , omp_get_num_threads());
printf( "sum  = %d\n" , sum );
	return sum;
}

//паралельное
int sum_arrparal(int *a, const int n, int p)
{
	int sum = 0;

	//omp_set_dynamic(0);      // Не менять число потоков во время исполнения
	omp_set_num_threads(p); // число потоков

	double t0 = omp_get_wtime();

#pragma omp parallel shared(a) reduction (+: sum) //num_threads(8)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
			sum += a[i];
	}
    double t1 = omp_get_wtime();
	printf("time for n core is  %.3f s \n", t1 - t0);
	printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
  //  printf("num threads = %d\n" , omp_get_num_threads());
    printf( "sum  = %d\n" , sum );
	return sum;
}


//последовательное
int max_arrpos(int *a, int n)
{
	int maxel = 0;
	double t0 = omp_get_wtime();
	for (int i = 0; i < n; ++i)
		if(a[i] > maxel)
            maxel = a[i];
	double t1 = omp_get_wtime();
	printf("time for 1 core is  %.3f s \n", t1 - t0);
	//printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
    //printf("num threads = %d\n" , omp_get_num_threads());
    printf( "max element  = %d\n" , maxel );
	return maxel;
}

//паралельное
int max_arrparal(int *a, const int n, int p)
{
	int maxel = 0;

	//omp_set_dynamic(0);      // Не менять число потоков во время исполнения
	omp_set_num_threads(p); // число потоков

	double t0 = omp_get_wtime();
int i;
#pragma omp parallel for private(i) shared(a,maxel)  //num_threads(8)
		for (i = 0; i < n; i++)
        {
            //#pragma omp critical
            if (a[i] > maxel)
            #pragma omp critical
                maxel = a[i];
        }

    double t1 = omp_get_wtime();
	printf("time for n core is  %.3f s \n", t1 - t0);
	printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
  //  printf("num threads = %d\n" , omp_get_num_threads());
    printf( "maxel  = %d\n" , maxel );
	return maxel;
}


void init(int n)
{
//	time_t t;
//	srand(1);
time_t t;
srand((unsigned)time(&t));

	cout << "Array: " << endl;
	for (int i = 0; i<n; i++)
	{
		a[i] = 2*(rand() % 1000)+1;
		//cout << " " << a[i];
	}
	cout << endl;

	return ;
}

int main()
{
	int n;
	printf( "Enter n: \n");
	scanf("%d", &n);
	init(n);
	printf( " 1 core \n");
	max_arrpos(a,n);
	printf( "\n");
	 max_arrparal(a, n, 1);
	printf( "\n");
	printf( " 2 core \n");
	 max_arrparal(a, n, 2);
	printf( "\n");
	printf( " 4 core \n");
	 max_arrparal(a, n, 4);
	printf( "\n");
	printf( "\n");
	/*sum_arrpos(a,n);
	printf( "\n");
	 sum_arrparal(a, n, 1);
	printf( "\n");
	printf( "\n");
	 sum_arrparal(a, n, 2);
	printf( "\n");
	printf( "\n");
	 sum_arrparal(a, n, 4);
	printf( "\n");
        printf( "\n");
	 sum_arrparal(a, n, 8);
	printf( "\n");
	printf( "\n");
	 sum_arrparal(a, n, 16);
	printf( "\n");
	printf( "\n");
	 sum_arrparal(a, n, 32);
	printf( "\n");
	printf( "\n");
	 sum_arrparal(a, n, 64);
	printf( "\n");*/

	//cout << "max thread = " << omp_get_max_threads() << endl;
	//cout << "num procs = " << omp_get_num_procs() << endl;

	/*
	//последовательное
	unsigned int start_timepos = clock();

	cout << "sum= " << sum_arrpos(a, n) << endl;

	unsigned int end_timepos = clock();
	unsigned int search_timepos = end_timepos - start_timepos;

	cout << "start time = " << start_timepos << endl;
	cout << "end time = " << end_timepos << endl;
	cout << "search time = " << search_timepos << endl;

	cout << endl << endl;

	//паралельное
	unsigned int start_timepar = clock();

	cout << "sum= " << sum_arrparal(a, n) << endl;

	unsigned int end_timepar = clock();
	unsigned int search_timepar = end_timepar - start_timepar;

	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "start time = " << start_timepar << endl;
	cout << "end time = " << end_timepar << endl;
	cout << "search time = " << search_timepar << endl;
	*/
	system("pause");
	return 0;
}


