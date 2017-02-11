#include <iostream>
#include <omp.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <ctime>
#include <time.h>

using namespace std;
int a[100000000];

//последовательное 
int sum_arrpos(int *a, int n)
{
	int sum = 0;
	int start_time = clock();
	for (int i = 0; i < n; ++i)
		sum += a[i];
	int end_time = clock();
	printf("time for 1 core = %d ms \n", end_time - start_time);
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;
	cout << "num threads = " << omp_get_num_threads() << endl;
	cout << "sum  = " << sum << endl;
	return sum;
}

//парарлельное на 1 потоке
int sum_arrparal1(int *a, const int n)
{
	int sum = 0;

	//omp_set_dynamic(0);      
	omp_set_num_threads(1);

	int start_time = clock();

#pragma omp parallel shared(a) reduction (+: sum) //num_threads(1)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
			sum += a[i];
		cout << "sum thread 1 = " << sum << endl;
	}
	int end_time = clock();
	printf("time for 1 core is  %d ms \n", end_time - start_time);
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;
	cout << "num threads = " << omp_get_num_threads() << endl;
	return sum;
}

//паралельное
int sum_arrparal(int *a, const int n)
{
	int sum = 0;

	//omp_set_dynamic(0);      // Не менять число потоков во время исполнения
	omp_set_num_threads(8); // число потоков

	int start_time = clock();

#pragma omp parallel shared(a) reduction (+: sum) //num_threads(8)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
			sum += a[i];
		cout << "sum thread = " << sum << endl;
	}
	int end_time = clock();
	printf("time = %d ms \n", end_time - start_time);
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;
	cout << "num threads = " << omp_get_num_threads() << endl;
	cout << "sum  = " << sum << endl;
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
		a[i] = rand() % 1000;
	}
	cout << endl;

	return;
}

int main(int argc, char **argv)
{
	int n;
	cout << "Enter n :";
	cin >> n;
	init(n);
	cout << endl;
	sum_arrparal1(a, n);
	cout << "------------------------\n";
	sum_arrpos(a, n);
	cout << "------------------------\n";
	sum_arrparal(a, n);
	cout << endl;


	system("pause");
	return EXIT_SUCCESS;
}




