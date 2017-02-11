#include <iostream>
#include <omp.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <ctime>
#include <math.h>

using namespace std;

//последовательное 
double sum_arrpos(int *a, const int n, int x, int m)
{
	double sum = 0;
	double del = 0;
	double ost = 0;
	int start_time = clock();
		for (int i = 0; i < n; ++i)
			sum += ((a[i]) * (pow(x, n - (i + 1))));
	del = (sum )/ (pow(x, n));
	ost = fmod(del, m);
	int end_time = clock();
	printf("time for 1 core = %d ms \n", end_time - start_time);
	cout << endl;
	cout << "sum = " << sum << endl;
	cout << "del = " << del << endl;
	cout << "ost = " << ost << endl;
	cout << endl;
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;
	cout << "\n\n\n";
	return ost;
}


//паралельное
double sum_arrparal(int *a, const int n, int x, int m)
{
	double sum = 0;
	double del = 0, ost = 0;

	//omp_set_dynamic(0);      // Не менять число потоков во время исполнения
	omp_set_num_threads(4); 

	int start_time = clock();
#pragma omp parallel shared(a) reduction (+: sum) //num_threads(2)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
		{
			sum += (a[i] * pow(x,n-(i+1)));
		}
	}
	del = sum / pow(x, n);
	ost = fmod(del, m);
	int end_time = clock();
	printf("time = %d ms \n", end_time - start_time);
	cout << endl;
	cout << "sum = " << sum << endl;
	cout << "del = " << del << endl;
	cout << "ost = " << ost << endl;
	cout << endl;
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;
	cout << "\n\n\n";
	return ost;
}


//последовательное 
double sum_arrpos1(int *a, const int n, int x, int m)
{	
	double sum = 0;
	double ost = 0;
	int start_time = clock();
	for (int i = 0; i < n; ++i)
		sum += ((a[i]) / (pow(x,i)));
	//ost = (int)sum % m;
	ost = fmod(sum, m);
	int end_time = clock();
	printf("time for 1 core = %d ms \n", end_time - start_time);
	cout << endl;
	cout << "sum = " << sum << endl;
	cout << "ost = " << ost << endl;
	cout << endl;
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;
	cout << "\n\n\n";
	return ost;
}


//паралельное
double sum_arrparal1(int *a, const int n, int x, int m)
{
	double sum = 0;
	double ost = 0;

	//omp_set_dynamic(0);      // Не менять число потоков во время исполнения
	omp_set_num_threads(4);

	int start_time = clock();
#pragma omp parallel shared(a) reduction (+: sum) //num_threads(2)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
		{
			sum += ((a[i]) / (pow(x, i)));
		}
	}
	//ost = (int)sum % m;
	ost = fmod(sum, m);
	int end_time = clock();
	printf("time = %d ms \n", end_time - start_time);
	cout << endl;
	cout << "sum = " << sum << endl;
	cout << "ost = " << ost << endl;
	cout << endl;
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;
	cout << "\n\n\n";
	return ost;
}


int *init(int n)
{
	time_t t;
	srand((unsigned)time(&t));

	int *arr = new int[n];

	cout << "Array: " << endl;
	for (int i = 0; i<n; i++)
	{
		arr[i] = rand() % 100;
	//	cout << " " << arr[i];
	}
	cout << endl;

	int *a;

	a = &arr[0];

	return a;
}

int main(int argc, char **argv)
{
	int n,m;
	int x;
	cout << "Enter n :";
	cin >> n;
	cout << "Enter x :";
	cin >> x;
	cout << "Enter m :";
	cin >> m;
	int *a = init(n);
	cout << endl;
	sum_arrpos(a, n, x, m); 
	sum_arrparal(a, n, x, m);

	sum_arrpos1(a, n, x, m);
	sum_arrparal1(a, n, x, m);

	system("pause");
	return EXIT_SUCCESS;
}


