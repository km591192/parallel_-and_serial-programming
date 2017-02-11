#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char **argv)
{
	omp_set_num_threads(2);
#pragma omp parallel 
	{
		cout << "hello world \n" << endl;
	}
	return EXIT_SUCCESS;
}