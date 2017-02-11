#include <iostream>
#include <omp.h>
#include <math.h>

using namespace std;

int sump (int n)
{
    int sum = 0;
    float mod = 0;
    int a[n];
    int i=0;

	double t0 = omp_get_wtime();
	{a[0] = 0;a[1] = 1;
	    if(n < 1) return 0;
        if(n == 1) return 1;
        omp_set_num_threads(8);
#pragma omp parallel  reduction (+: sum) //num_threads(1)
	{
# pragma omp for
		for ( i = 2; i < n; i++)
			a[i] = a[i-1] + a[i-2];
# pragma omp for
		for ( i = 0; i < n; i++)
			sum += a[i];
}
mod = fmod(sum,(pow(2,64)));
double t1 = omp_get_wtime();
	printf("time for x core is  %.3f s \n", t1 - t0);
	//printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
//printf("num threads = %d\n" , omp_get_num_threads());
printf( "sum  = %d\n" , sum );
printf( "mod  = %f\n" , mod );
	return mod;
}
}

int Fib(int i)
{
if(i < 1) return 0;
if(i == 1) return 1;
return Fib(i-1) + Fib(i - 2);
}

int sum (int n)
{
    int sum = 0;
    float mod = 0;
   // omp_set_num_threads(8);
    int a[n];

	double t0 = omp_get_wtime();

	{
		for (int i = 0; i < n; i++)
        {
			sum += Fib(i);
        }
}
mod = fmod(sum,(pow(2,64)));
double t1 = omp_get_wtime();
	printf("time for x core is  %.3f s \n", t1 - t0);
	//printf("max thread = %d\n", omp_get_max_threads());
	//printf("num procs = %d\n", omp_get_num_procs());
//printf("num threads = %d\n" , omp_get_num_threads());
printf( "sum  = %d\n" , sum );
printf( "mod  = %f\n" , mod );
	return mod;
}

int main()
{
    int n;
	printf( "Enter n: \n");
	scanf("%d", &n);
    sum(n);
    printf("\n");
    //sump(n);
    return 0;
}

