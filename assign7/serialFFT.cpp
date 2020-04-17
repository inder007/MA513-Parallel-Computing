#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

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

void iterative_FFT(int n, complex<double>* a, complex<double>* abrc, int flag){
	int r=log2(n);
    
	for(int i=0;i<n;i++){
		// cout<<rev(i, r)<<" ";
		abrc[rev(i, r)] = a[i]; 
	}

	for(int s=1;s<=r;s++){
		int m = (1<<s);
		complex<double> wm = {cos((2*pi*flag)/m), sin(2*pi*flag/m)};
		// complex<double> wm(cos(pi), sin(pi));
		for(int k=0;k<n;k+=m){
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

}


int main(int argc, char** argv){
	int orig_n = atoi(argv[1]);
	int n = 2*orig_n;

	complex<double>* a = new complex<double>[n];
	complex<double>* b = new complex<double>[n];

	for(int i=0;i<n;i++){
		if(i<orig_n){
			a[i] = {1,0};
			b[i] = {1,0};
		}
		else{
			a[i] = {0,0};
			b[i] = {0,0};
		}
		
	}

	complex<double>* abrc = new complex<double>[n];
	complex<double>* bbrc = new complex<double>[n];

	

	// cout<<endl;

	// cout<<pi<<endl;
	// cout<<M_PI<<endl;


	iterative_FFT(n, a, abrc, 1);
	iterative_FFT(n, a, bbrc, 1);

	complex<double>* y_prod = new complex<double>[n];
	for(int i=0;i<n;i++){
		y_prod[i] = abrc[i]*bbrc[i];
	}


	// complex<double>* abrc_interpolation = new complex<double>[n];
	// complex<double>* bbrc_interpolation = new complex<double>[n];

	complex<double>* interpolation = new complex<double>[n];

	iterative_FFT(n, y_prod, interpolation, -1);
	// iterative_FFT(n, abrc, abrc_interpolation, -1);

	for(int i=0;i<n-1;i++){
		cout<<real(interpolation[i])/n<<" ";
	}
	cout<<endl;

	return 0;
}