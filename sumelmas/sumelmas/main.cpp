#include <iostream>
#include <omp.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <ctime>

using namespace std;

//последовательное 
int sum_arrpos(int *a, int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
		sum += a[i];
	return sum;
}


//паралельное
int sum_arrparal(int *a, const int n)
{
	int sum = 0;
	
	//omp_set_dynamic(0);      // Не менять число потоков во время исполнения
	//omp_set_num_threads(4); // число потоков

#pragma omp parallel shared(a) reduction (+: sum) //num_threads(2)
	{
# pragma omp for
		for (int i = 0; i < n; ++i)
			sum += a[i];
	}

	return sum;
}


int *init(int n)
{
	time_t t;
	srand((unsigned)time(&t));

	int *arr = new int[n];

	cout << "Array: " << endl;
	for (int i = 0; i<n; i++)
	{
		arr[i] = rand() % 1000;
		cout << " " << arr[i];
	}
	cout << endl;

	int *a;

	a = &arr[0];

	return a;
}

int main(int argc, char **argv)
{
	int n;
	cout << "Enter n :";
	cin >> n;
	int *a = init(n);
	cout << endl;
	cout << "sum= " << sum_arrparal(a, n) << endl;
	cout << endl;
	cout << "max thread = " << omp_get_max_threads() << endl;
	cout << "num procs = " << omp_get_num_procs() << endl;

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
	
	return EXIT_SUCCESS;
}


/*#pragma omp parallel
{
#pragma for shared(x) private(i) reduction(+:sum)
 for(i=0; i<10000; i++)
 sum += x[i];
}*//*
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