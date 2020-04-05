#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int my_id, size;

    int n = atoi(argv[1]);

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int no_per_process = n/size;

	float* a = (float*)malloc(sizeof(float)*n*no_per_process);
	float* recvA = (float*)calloc(n, sizeof(float));

	int root_process = 0;
	if(my_id == root_process){
		float* arr = (float*)malloc(sizeof(float)*n*n);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				// arr[i*n + j] = i*n + j + 1;
				if(i>=j){
                    arr[i*n+j] = j+1;
                } else {
                    arr[i*n+j] = 0;
                }
				// printf("%f ", arr[i*n+j]);
			}
			// printf("\n");
		}
		// printf("\n");

		for(int i=0;i<n;i++){
			if(i%size == root_process){
				for(int j=0;j<n;j++){
					a[(i/size)*n + j] = arr[i*n + j];
				}
			}
			else{
				MPI_Send(&arr[i*n], n, MPI_FLOAT, i%size, 0, MPI_COMM_WORLD);
				// for(int j=0;j<n;j++){
				// 	MPI_Send(&arr[i*n+j], 1, MPI_FLOAT, i%size, 0, MPI_COMM_WORLD);
				// }
			}
		}
	}
	else{
		for(int i=0;i<no_per_process;i++){
			MPI_Recv(&a[i*n], n, MPI_FLOAT, root_process, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			// for(int j=0;j<n;j++){
			// 	MPI_Recv(&a[i*n + j], 1, MPI_FLOAT, root_process, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			// }
		}
	}

	// MPI_Barrier(MPI_COMM_WORLD);
	// for(int i=0;i<no_per_process;i++){
	// 	printf("%d %d ", my_id, i*size + my_id );
	// 	for(int j=0;j<n;j++){
	// 		printf("%f ", a[i*n+j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");

	double t1, t2, pt, time, pt2;
	MPI_Barrier(MPI_COMM_WORLD);

	t1 = MPI_Wtime();
	for(int i=0;i<n;i++){
		if(i%size == my_id){
			int r = a[(i/size)*n + i];
			for(int j=i;j<n;j++){
				a[(i/size)*n + j] /= r;
				recvA[j] = a[(i/size)*n + j];
			}
			MPI_Bcast(&recvA[i], n-i, MPI_FLOAT, i%size, MPI_COMM_WORLD);
			for(int j = (i/size) + 1;j<no_per_process;j++){
				int x = a[j*n + i];
				for(int k=i;k<n;k++){
					a[j*n + k] -= recvA[k]*x;
				}
			}
		}
		else{
			MPI_Bcast(&recvA[i], n-i, MPI_FLOAT, i%size, MPI_COMM_WORLD);
			int j;
			if(my_id > i%size){
				j = i/size;
			}
			else{
				j = i/size + 1;
			}
			for(;j<no_per_process;j++){
				int x = a[j*n + i];
				for(int k=i;k<n;k++){
					a[j*n + k] -= recvA[k]*x;
				}
			}
		}

	}


	t2 = MPI_Wtime();
	MPI_Reduce(&t1, &pt, 1, MPI_DOUBLE, MPI_MIN, root_process, MPI_COMM_WORLD);
	MPI_Reduce(&t2, &pt2, 1, MPI_DOUBLE, MPI_MAX, root_process, MPI_COMM_WORLD);
	// pt = t2 - t1;
	if(my_id == root_process){
		// printf("Time elapsed is %lf \n", time);
		time = pt2 - pt;
		printf("%lf\n", time);
	}

	// for(int i=0;i<no_per_process;i++){
	// 	printf("%d %d ", my_id, i*size + my_id );
	// 	for(int j=0;j<n;j++){
	// 		printf("%f ", a[i*n+j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");

	MPI_Finalize();
	return 0;
}