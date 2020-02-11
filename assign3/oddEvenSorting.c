#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


void merge(int l, int mid, int h, int* arr){
	int* a = (int*)malloc(sizeof(int)*(mid-l+1));
	int* b = (int*)malloc(sizeof(int)*(h-mid+1));
	int x=0,y=0;
	for(int i=l;i<=mid;i++){
		a[x++] = arr[i];
	}
	for(int i=mid+1;i<=h;i++){
		b[y++] = arr[i];
	}
	int j=0,k=0;
	for(int i=l;i<=h;i++){
		if(j<x && k<y){
			if(a[j]<=b[k]){
				arr[i] = a[j++];
			}
			else{
				arr[i] = b[k++];
			}
		}
		else if(j<x){
			arr[i] = a[j++];
		}
		else{
			arr[i] = b[k++];
		}
	}
	free(a);
	free(b);
}

void mergesort(int l, int h, int* arr){
	if(h>l){
		int mid=(l+h)/2;
		mergesort(l, mid, arr);
		mergesort(mid+1, h, arr);
		merge(l, mid, h, arr);
	}
}

int main(int argc, char** argv){
    int my_id, size;

    int n = atoi(argv[1]);

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int no_per_process = n/size;
	int root_process = 0;

	int* arr = (int*)malloc(sizeof(int)*n);
	int* arr1 = (int*)malloc(sizeof(int)*no_per_process*2);

	if(my_id == root_process){
		for(int i=0;i<n;i++){
			arr[i] = n-i;
		}
		// mergesort(0, n-1, arr);
		// for(int i=0;i<n;i++){
		// 	printf("%d ", arr[i]);
		// }
		// printf("\n");
	}

	MPI_Scatter(arr, no_per_process, MPI_INT, arr1, no_per_process, MPI_INT, root_process, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	double t1, t2, pt, time, pt2;

	t1 = MPI_Wtime();
	mergesort(0, no_per_process-1, arr1);

	for(int i=0;i<size;i+=2){
		if(my_id%2==0 && my_id+1<size){
			MPI_Recv(&arr1[no_per_process], no_per_process, MPI_INT, my_id+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			merge(0, no_per_process-1,2*no_per_process-1,arr1);
		}
		else if(my_id%2==1 && my_id-1>=0){
        	MPI_Send(arr1, no_per_process, MPI_INT, my_id-1, 0, MPI_COMM_WORLD);
		}
		if(my_id%2==0 && my_id+1<size){

        	MPI_Send(&arr1[no_per_process], no_per_process, MPI_INT, my_id+1, 0, MPI_COMM_WORLD);
		}
		else{
			MPI_Recv(arr1, no_per_process, MPI_INT, my_id-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		MPI_Barrier(MPI_COMM_WORLD);
		
		if(my_id%2==1 && my_id+1<size){
			MPI_Recv(&arr1[no_per_process], no_per_process, MPI_INT, my_id+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			merge(0, no_per_process-1,2*no_per_process-1,arr1);
		}
		else if(my_id%2==0 && my_id-1>=0){

        	MPI_Send(arr1, no_per_process, MPI_INT, my_id-1, 0, MPI_COMM_WORLD);
		}
		if(my_id%2==1 && my_id+1<size){

        	MPI_Send(&arr1[no_per_process], no_per_process, MPI_INT, my_id+1, 0, MPI_COMM_WORLD);
		}
		else if(my_id%2==0 && my_id-1>=0){
			MPI_Recv(arr1, no_per_process, MPI_INT, my_id-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}


	MPI_Gather(arr1, no_per_process, MPI_INT, arr, no_per_process, MPI_INT, root_process, MPI_COMM_WORLD);
	// if(root_process == my_id){
	// 	printf("%d\n", my_id);
	// 	for(int i=0;i<n;i++){
	// 		printf("%d ", arr[i]);
	// 	}
	// 	printf("\n");
	// }
	// else{
	// 	MPI_Gather(arr1, no_per_process, MPI_INT, NULL, 0, MPI_INT, root_process, MPI_COMM_WORLD);
	// }
	
	t2 = MPI_Wtime();
	MPI_Reduce(&t1, &pt, 1, MPI_DOUBLE, MPI_MIN, root_process, MPI_COMM_WORLD);
	MPI_Reduce(&t2, &pt2, 1, MPI_DOUBLE, MPI_MAX, root_process, MPI_COMM_WORLD);

	if(my_id == root_process){
		time = pt2 - pt;
		printf("%lf\n", time);
	}

	MPI_Finalize();

	return 0;
}