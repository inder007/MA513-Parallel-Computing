#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const double pi = acos(-1);

int numThreads;
pthread_barrier_t barrier;

struct thread_data{
	complex<double>* a;
	complex<double>* b;
	complex<double>* c;
	int n;
	int id;
};

int rev(int a, int r){
	int number = a;
	string temp="";
	while(number){
		temp += (number%2+'0');
		number/=2;
	}

	for(int j=temp.size();j<r;j++){
		temp += '0';
	}
	int ans=0;
	for(int i=0;i<r;i++){
		if(temp[i]=='1'){
			ans += (1<<(r-i-1));
		}
	}
	return ans;
}

void iterative_FFT(int n, complex<double>* abrc, int flag, int id){
	int r=log2(n);
	int x = log2(numThreads);
	int numPerProcessor = n/numThreads;
    int start = id*numPerProcessor;
    int end = (id+1)*numPerProcessor;

	complex<double>* temp = new complex<double>[n];

	for(int i=start;i<end;i++){
		if(i<rev(i,r)){
			swap(abrc[rev(i,r)], abrc[i]);
		}
	}


	
	pthread_barrier_wait(&barrier);
	for(int s=1;s<=r-x;s++){

		int m = (1<<s);
		complex<double> wm = {cos((2*pi*flag)/m), sin(2*pi*flag/m)};
		for(int k=start;k<end;k+=m){
			complex<double> w(1,0);
			for(int j=0;j<m/2;j++){
				complex<double> t(w*abrc[k+j+m/2]);
				complex<double> u(abrc[k+j]);
				abrc[k+j] = u + t;
				abrc[k+j+m/2] = u - t;
				w = w*wm;
			}
		}
		
	}

	for(int s=1;s<=x;s++){
		// pthread_barrier_wait(&barrier);
		int o = s+r-x;
		int m = (1<<o);
		int checkSide = (1<<s);
		complex<double> wm = {cos((2*pi*flag)/m), sin(2*pi*flag/m)};
		
		complex<double> w(1,0);
		complex<double> wperprocessor(1,0);
		for(int p=0;p<numPerProcessor;p++){
			wperprocessor *= wm;
		}
		if(id%checkSide>=checkSide/2){
			for(int p=0;p<(id-checkSide/2);p++){
				w *= wperprocessor;
			}
		}
		else{
			for(int p=0;p<(id);p++){
				w *= wperprocessor;
			}
		}
		pthread_barrier_wait(&barrier);
		for(int k=start;k<end;k++){
			
			complex<double> t;
			complex<double> u;
			if(id%checkSide>=checkSide/2){
				t = w*abrc[k];
				u = abrc[k-m/2];
			}
			else{
				u = abrc[k];
				t = w*abrc[k+m/2];
			}

			if(id%checkSide>=checkSide/2){
				temp[k] = u-t;
			}
			else{
				temp[k] = u+t;
			}
			w = w*wm;

		}
		pthread_barrier_wait(&barrier);
		for(int i=start;i<end;i++){
			abrc[i] = temp[i];
		}

	}

	delete temp;
}

void* job(void* thread_args){
	thread_data* data = (thread_data*) thread_args;
	int n = data->n;
	complex<double>* a = data->a;
	complex<double>* b = data->b;
	complex<double>* c = data->c;
	int id = data->id;

	int numPerProcessor = n/numThreads;

	iterative_FFT(n, a, 1, id);
	iterative_FFT(n, b, 1, id);


	for(int i=id*numPerProcessor;i<(id+1)*numPerProcessor;i++){
		c[i] = a[i]*b[i];
	}

	pthread_barrier_wait(&barrier);

	iterative_FFT(n, c, -1, id);
}


int main(int argc, char** argv){
	int orig_n = atoi(argv[1]);
	int n = 2*orig_n;
	numThreads = atoi(argv[2]);

	complex<double>* a = new complex<double>[n];
	complex<double>* b = new complex<double>[n];
	complex<double>* c = new complex<double>[n];

	for(int i=0;i<n;i++){
		if(i<orig_n){
			a[i] = {1,0};
			b[i] = {1,0};
		}
		else{
			a[i] = {0,0};
			b[i] = {0,0};
		}
		// c[i] = {i,0};
		
	}

	// job((void*) &args);

	pthread_t threads[numThreads];

	thread_data* threadargs = new thread_data[numThreads];

	for(int i=0;i<numThreads;i++){
		threadargs[i] = {a, b, c, n, i};
	}

	pthread_barrier_init(&barrier, NULL, numThreads);

	double startTime, endTime;
    startTime = omp_get_wtime();

	for(int i=0;i<numThreads;i++){
		// thread_data args = {a, b, c, n, threadIds[i]};
		int r=pthread_create(&threads[i], NULL, job, (void*) &threadargs[i]);
		if(r){
			cout<<"ERROR"<<endl;
		}
	}	

	for(int i=0;i<numThreads;i++){
		int r = pthread_join(threads[i],NULL);
		if(r){
			cout<<"join error"<<endl;
		}
	}

	endTime = omp_get_wtime();
	cout<<endTime-startTime<<endl;

	// for(int i=0;i<n-1;i++){
	// 	cout<<real(a[i])<<" ";
	// }
	// cout<<endl;

	// for(int i=0;i<n-1;i++){
	// 	cout<<real(b[i])<<" ";
	// }
	// cout<<endl;

	// for(int i=0;i<n-1;i++){
	// 	cout<<real(c[i])/n<<" ";
	// }
	// cout<<endl;

	return 0;
}