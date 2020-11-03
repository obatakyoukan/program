#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<double,double > mp;
double inf =  1e9;
#define EPS 1e-4

int main(){
	int n;
	cin>>n;
	vector<mp> a(n);
	double uy = inf,dy = 0;
	for(int i=0;i<n;i++){
		double x,r;
		cin>>x>>r;
		a[i] = mp(x,r);
		//lx = max(lx,x-r);
		//rx = min(rx,x+r);
		uy = min(uy,r);
	}
	while(uy-dy>EPS){
		double lx = 0;
		double rx = inf;
		double y = (uy + dy)/2;
		for(int i=0;i<n;i++){
		    double r = a[i].second;
		    double x = a[i].first;
		    lx = max(lx,x-sqrt(r*r-y*y) );
		    rx = min(rx,x+sqrt(r*r-y*y) );
		}
		if(lx > rx){
			uy = y;
		}else{
			dy = y;
		}

	}
//	cout<< (uy+dy)/2 << endl;
	printf("%0.10lf\n",(uy+dy)/2);
	return 0;
}

