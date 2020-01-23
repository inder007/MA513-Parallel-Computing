#include <iostream>
using namespace std;

void normal(int* a, int* b, int* c, int n){
	for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
    		for(int k=0;k<n;k++){
    			c[n*i+j] += a[n*i + k]*b[n*k + j];
    		}
    	}
    }	
}

void opt1(int* a, int* b, int* c, int n){
	for(int i=0;i<n;i++){
    	for(int k=0;k<n;k++){
    		for(int j=0;j<n;j++){
    			c[n*i+j] += a[n*i + k]*b[n*k + j];
    		}
    	}
    }
}

void opt2(int* a, int* b, int* c, int n, int s){
	int q=n/s;
	for(int x=0;x<q;x++){
		for(int y=0;y<q;y++){
			for(int z=0;z<q;z++){
				for(int i=0;i<s;i++){
					for(int j=0;j<s;j++){
						for(int k=0;k<s;k++){
							c[(n*x+ y)*s + (n*i + j)] += a[(x*n + z)*s + (n*i + k)]*b[(z*n + y)*s + (n*k + j)];
						}
					}
				}
			}
		}	
	}
}

void rec(int* a, int* b, int* c, int i1, int j1, int i2, int j2, int i3, int j3, int n, int s){
	if(s==1){
		c[n*i3 + j3] += a[n*i1 + j1]*b[n*i2+j2];
	}
	else{
		rec(a, b, c, i1, j1, i2, j2, i3, j3, n, s/2); 
		rec(a, b, c, i1, j1+s/2, i2+s/2, j2, i3, j3, n, s/2);
		rec(a, b, c, i1, j1, i2, j2+s/2, i3, j3+s/2, n, s/2);
		rec(a, b, c, i1, j1+s/2, i2+s/2, j2+s/2, i3, j3+s/2, n, s/2);
		rec(a, b, c, i1+s/2, j1, i2, j2, i3+s/2, j3, n, s/2);
		rec(a, b, c, i1+s/2, j1+s/2, i2+s/2, j2, i3+s/2, j3, n, s/2);
		rec(a, b, c, i1+s/2, j1, i2, j2+s/2, i3+s/2, j3+s/2, n, s/2);
		rec(a, b, c, i1+s/2, j1+s/2, i2+s/2, j2+s/2, i3+s/2, j3+s/2, n, s/2);
	}
}

void set(int* a, int* b, int* c, int n){
	for(int i=0;i<4;i++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				a[n*i+j] = i;
				b[n*i+j] = i-1;
				c[n*i+j] = 0;
			}
		}
	}
}

void print(int* a, int* b, int* c, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<c[n*i+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int main(){
	int n, s;
	// n=16;
	cin>>n>>s;
	// int arr[n][n];
	// int a[n*n], b[n*n];
	int* a = new int[n*n];
	int* b = new int[n*n];
	int* c = new int[n*n];
	
	for(int i=1;i<=4;i++){
		set(a,b,c,n);
		if(i==1){
			normal(a,b,c,n);
		}
		else if(i==2){
			opt1(a,b,c,n);
		}
		else if(i==3){
			opt2(a,b,c,n,s);
		}
		else{
			rec(a,b,c,0,0,0,0,0,0,n,n);
		}
		print(a,b,c,n);
	}
	
    
    
	return 0;
}