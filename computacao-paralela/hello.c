#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
	//omp_set_num_threads(200);
	#pragma omp parallel
	{
	int a = omp_get_thread_num();
    printf("Hello world! %d \n", a);
    printf("Bye bye! %d \n", a);
	}
    return 0;
}