#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,ld> mp;
ld inf = 1e9;

ld dis(mp a,mp b){
	return sqrt( (a.first-b.first)*(a.first-b.first) + (a.second-b.second) * (a.second - b.second) );
}

int main(){
	int n;
	cin>>n;
	vector<mp> a(n);
	for(int i=0;i<n;i++)cin>>a[i].first>>a[i].second;
	vector<vector<ld> > dp(n,vector<ld>(n,inf) );
	sort(a.begin(),a.end());
	dp[0][0] = 0;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-1;j++){
			int t = max(i,j) + 1;
			dp[t][j] = min( dp[t][j], dp[i][j] + dis( a[i] , a[t] ) );
			dp[i][t] = min( dp[i][t], dp[i][j] + dis( a[j] , a[t] ) );
		}
	}
	ld res = inf ;
	for(int i=0;i<n-1;i++) res = min( res,  dp[n-1][i]  + dis( a[i] , a[n-1] ) );
	printf("%0.10lf\n",(double) res);
	return 0;
}

