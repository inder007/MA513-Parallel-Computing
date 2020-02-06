#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int my_id, size, n, no_per_process, sum=0, levels=0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	n=atoi(argv[1]);
	int* arr = (int*)malloc(sizeof(int)*n);

	int partial_sum=0, templevel=0, id, tl, psum;
	no_per_process = n/size;
	int r=size;
	while(r!=0){
		levels++;
		r=r>>1;
	}
	levels--;
	int root_process = 0;

	if(my_id == root_process){
		for(int i=0;i<n;i++){
			arr[i] = i+1;
		}
		
		int templevel=levels;
		// templevel--;
		int start=n;
		int pid = size;
		while(templevel>0){
			templevel--;
			start = start >> 1;
        	pid = pid>>1;
        	MPI_Send(&arr[start], start, MPI_INT, pid, 0, MPI_COMM_WORLD);
		}
		// for(int i=0;i<no_per_process;i++){
		// 	sum+=
		// }
	}
	else{
		int get_level=0;
		int id = my_id;
		while(id%2==0){
			get_level++;
			id = id>>1;
		}
		get_level = levels - get_level;
		// printf("id: %d, level: %d\n",my_id, get_level );
		MPI_Recv(arr,n/(1<<(get_level)), MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		// printf("id: %d, level: %d\n",my_id, get_level );

		int start = n/(1<<(get_level));
		int temp= levels-get_level;
		while(temp){
			temp--;
			start = start>>1;
        	// printf("%d sending to %d\n", my_id, my_id + (1<<temp));
        	MPI_Send(&arr[start], start, MPI_INT, my_id+(1<<temp), 0, MPI_COMM_WORLD);
			// get_level++;
			// temp--;
		}
		// printf("%d %d %d\n",arr1[0], arr1[1], my_id );

		id = my_id;
		templevel=0;
		while(id%2==0){
			templevel++;
			id = id>>1;
		}
		tl = templevel;

	}

	double t1, t2, pt, time;
	MPI_Barrier(MPI_COMM_WORLD);
	
	t1 = MPI_Wtime();
	if(my_id == root_process){
		for(int i=0;i<no_per_process;i++){
			sum+=arr[i];
		}
		// id = my_id;
		templevel = 0;
		while(templevel<levels){
	// printf("test\n");
			partial_sum=0;
			MPI_Recv(&partial_sum, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			templevel++;
			sum += partial_sum;
		}
	}	
	else{
		partial_sum=0;
		for(int i=0;i<no_per_process;i++){
			partial_sum+=arr[i];
		}
		
		while(templevel>0){
			psum=0;
			MPI_Recv(&psum, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			partial_sum += psum;
			templevel--;
		}
		// printf("%d sending to %d\n",my_id, my_id -(1<<tl) );
        MPI_Send(&partial_sum, 1, MPI_INT, my_id-(1<<tl), 0, MPI_COMM_WORLD);
	}

	t2 = MPI_Wtime();
	pt = t2 - t1;
	MPI_Reduce(&pt, &time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	if(my_id == root_process){
		// printf("%d\n", sum);
		// printf("Time elapsed is %lf \n", time);
		printf("%lf\n", time);
	}
	MPI_Finalize();
	return 0;
}