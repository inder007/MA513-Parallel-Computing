#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

void print(int* a, int* b, int* c, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<c[n*i+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int main(int argc, char *argv[]){
	int n;
	n=16;
	if(argc >= 2){
		n = atoi(argv[1]);
		// cout << n << endl;
	}
	// cin>>n;
	// int arr[n][n];
	// int a[n*n], b[n*n];
	int* a = new int[n*n];
	int* b = new int[n*n];
	int* c = new int[n*n]();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[n*i+j] = i+j;
			b[n*i+j] = i+j;
		}
	}
	auto start = chrono::high_resolution_clock::now();
	int iter_i=0, iter_k=0;
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
    		iter_k = 0;
    		for(int k=0;k<n;k++){
    			// c[n*i+j] += a[n*i + k]*b[n*k + j];
    			c[iter_i + j] += a[iter_i + k]*b[iter_k + j];
    			iter_k += n;
    		}
    	}
    	iter_i += n;
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 

    time_taken *= 1e-9; 
  
    cout << "Naive: Time taken by program is : " << fixed  
         << time_taken << setprecision(9); 
    cout << " sec" << endl; 
    // print(a,b,c,n);
	return 0;
}