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
	int s=32;
	if(argc >= 3){
		s = atoi(argv[2]);
	}
	// cin>>n;
	// cin>>s;
	int* a = new int[n*n];
	int* b = new int[n*n];
	int* c = new int[n*n]();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[n*i+j] = i+j;
			b[n*i+j] = i+j;
		}
	}
	int q=n/s;
	int iter_x, iter_z, iter_i, iter_k, xic = 0, yc, zc, zic;
	int tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
	int p = n*s;
	iter_x = 0;
	auto start = chrono::high_resolution_clock::now();
	for(int x=0;x<q;x++){
		// xic = iter_x*s;
		iter_z=0;
		zc = zic = 0;
		for(int z=0;z<q;z++){
			// zc = z*s;
			// zic = iter_z*s;
			yc = 0;
			tmp3 = xic + zc;
			for(int y=0;y<q;y++){
				// yc = y*s;
				tmp1 = xic + yc;
				tmp5 = zic + yc;
				iter_i=0;
				for(int i=0;i<s;i++){
					iter_k=0;
					tmp2 = tmp1 + iter_i; 
					tmp4 = tmp3 + iter_i;
					for(int k=0;k<s;k++){
						tmp6 = tmp5 + iter_k;
						tmp7 = tmp4 + k;
						tmp8 = tmp2;
						tmp9 = tmp6;
						for(int j=0;j<s;j++){
							// c[(n*x+ y)*s + (n*i + j)] += a[(x*n + z)*s + (n*i + k)]*b[(z*n + y)*s + (n*k + j)];
							// c[xic + yc + iter_i + j] += a[xic + zc + iter_i + k]*b[zic + yc + iter_k + j];
							// c[tmp2 + j] += a[tmp7]*b[tmp6 + j];
							c[tmp8] += a[tmp7]*b[tmp9];
							tmp8++;
							tmp9++;
						}
						iter_k += n;
					}
					iter_i += n;
				}
				yc += s;
			}
			zc += s;
			zic += p;
			iter_z += n;
		}
		iter_x += n;
		xic += p;
	}
	auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 

    time_taken *= 1e-9; 
  
    cout << "Opt2_swap: Time taken by program is : " << fixed  
         << time_taken << setprecision(9); 
    cout << " sec" << endl; 
	// print(a,b,c,n);
	return 0;
}