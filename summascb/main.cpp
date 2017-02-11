#include <iostream>
#include <omp.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <ctime>
#include <time.h>

using namespace std;
int a[400000000];

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

#pragma omp parallel shared(a) reduction (*: sum) //num_threads(1)
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
	int sum = 1;

	//omp_set_dynamic(0);      // Не менять число потоков во время исполнения
	omp_set_num_threads(p); // число потоков

	double t0 = omp_get_wtime();

#pragma omp parallel shared(a) reduction (*: sum) //num_threads(8)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
			sum *= a[i];
	}
    double t1 = omp_get_wtime();
	printf("time for n core is  %.3f s \n", t1 - t0);
	printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
  //  printf("num threads = %d\n" , omp_get_num_threads());
    printf( "sum  = %d\n" , sum );
	return sum;
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
	//scanf("%d", &n);
	n = 300000000;
	init(n);
	sum_arrpos(a,n);
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
	printf( "\n");
	//-----------------------
	n = 200000000;
	sum_arrpos(a,n);
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
	printf( "\n");
	//----------------------------
	n=100000000;
	sum_arrpos(a,n);
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
	printf( "\n");
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


/*#pragma omp parallel
{
#pragma for shared(x) private(i) reduction(+:sum)
 for(i=0; i<10000; i++)
 sum += x[i];
}
*/

/*
//init array
time_t t;
srand((unsigned)time(&t));

int n;
cout << "Enter n :";
cin >> n;

int *arr = new int[n];

cout << "Array: " << endl;
for (int i = 0; i<n; i++)
{
arr[i] = rand() % 20;
cout << " " << arr[i];
}
cout << endl;

int *a;

a = &arr[0];*/

