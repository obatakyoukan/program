#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<double,double> mp;
#define inf 1e9


int main(){
	int n;
	cin>>n;
	vector<double> a(n+1,0);
	for(int i=1;i<=n;i++)cin>>a[i];
	vector<double> res(n+1);
	res[0] = 0;
	for(int i=1;i<=n;i++){
	    	double ma = a[i] ;
		for(int j=i-1;j>=0;j--){
			ma = max(ma, res[j] + sqrt( (a[i]+a[j])*(a[i]+a[j]) - (a[i]-a[j])*(a[i]-a[j]) ) );
		}
		res[i] = ma;
	}

	double ans = 0;
	for(int i=0 ; i<=n; i++){
	    ans= max(ans,res[i]+a[i]) ;
	}
	printf("%0.10lf\n",ans);
	return 0;	
}

