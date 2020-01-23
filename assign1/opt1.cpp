#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
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
	int iter_i=0, iter_k=0, tmp1, tmp2, tmp3;
	auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<n;i++){
    	iter_k=0;
    	for(int k=0;k<n;k++){
    		tmp1 = iter_i + k;
    		tmp2 = iter_i;
    		tmp3 = iter_k;
    		for(int j=0;j<n;j++){
    			// c[n*i+j] += a[n*i + k]*b[n*k + j];
    			c[tmp2] += a[tmp1]*b[tmp3];
    			tmp2++;
    			tmp3++;
    		}
    		iter_k+=n;
    	}
    	iter_i+=n;
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 

    time_taken *= 1e-9; 
  
    cout << "Opt1: Time taken by program is : " << fixed  
         << time_taken << setprecision(9); 
    cout << " sec" << endl; 

    // print(a,b,c,n);
	return 0;
}