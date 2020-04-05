#include<omp.h>
#include <stdio.h>

int main(){
	#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		printf("hello %d", id);
		printf("world %d \n", id);

	}


	return 0;
}