#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define popb pop_back
#define vi vector<int>
#define vll vector<ll>
#define vvi vector < vi >
#define pii pair<int,int>
#define pll pair<long long, long long>
#define all(c) c.begin(),c.end()
#define mp make_pair
#define f first
#define s second
typedef long long ll;
typedef unsigned long long ull;

double func(double n){
	return (4*n*n*n - n*n)/(1.9e9);
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<func(32)<<endl;
    cout<<func(64)<<endl;
    cout<<func(128)<<endl;
    cout<<func(256)<<endl;
    cout<<func(512)<<endl;
    cout<<func(1024)<<endl;
    cout<<func(2048)<<endl;
    cout<<func(4096)<<endl;
    cout<<func(8192)<<endl;
    
	return 0;
}