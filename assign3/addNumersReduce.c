#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int my_id, size, n, no_per_process, sum=0, partial_sum=0;
	MPI_Status status;
	// printf("please enter the number of numbers to sum: ");
 //    scanf("%i", &n);
	int arr[1000];
	n=atoi(argv[1]);
	// printf("%d\n", n);
	// int arr1[1000];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    no_per_process = n/size;

	int root_process=0;
	if(my_id == root_process){
        	// printf("test\n");
	    for(int i=0;i<n;i++){
	    	arr[i] = i+1;
	    }
        for(int i=1;i<size;i++){
        	int start=i*no_per_process;
        	MPI_Send(&arr[start], no_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        // for(int i=0;i<no_per_process;i++){
        // 	partial_sum += arr[i];
        // }
        
	}
	else{
		MPI_Recv(&arr, no_per_process, MPI_INT, root_process, 0, MPI_COMM_WORLD, &status);
		// for(int i=0;i<no_per_process;i++){
  //       	partial_sum += arr1[i];
  //       }
	}

	double t1, t2, pt, time;
	t1 = MPI_Wtime();

	for(int i=0;i<no_per_process;i++){
    	partial_sum += arr[i];
    }

	MPI_Reduce(&partial_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    t2 = MPI_Wtime();
	pt = t2 - t1;
	MPI_Reduce(&pt, &time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if(my_id == 0){
    	printf("Total Sum: %d\n", sum);
		printf("Time elapsed is %lf \n", time);
    }
    MPI_Finalize();
	return 0;
}