#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int n;
    cin>>n;
    vector<int> a(3,0);
    for(int i=0;i<n;i++){
	int tmp;
	cin>>tmp;
	tmp--;
	a[tmp]++;
    }
    vector<vector<vector<double> > > dp(n+1,vector<vector<double> >(n+1,vector<double>(n+1,0) ) );

    for(int i=0;i<=n;i++){
	for(int j=0;j<=n;j++){
	    for(int k=0;k<=n;k++){
		double sum = 0;
		if(i+j+k==0)continue;
		if( k>0 ) sum += dp[i][j][k-1]*k/(i+j+k);
		if( j>0 && k< n ) sum += dp[i][j-1][k+1]*j/(i+j+k);
		if( i>0 && j< n ) sum += dp[i-1][j+1][k]*i/(i+j+k);
		dp[i][j][k] = sum + (double) n /(i+j+k);
	    }
	}
    }
    printf("%0.10lf\n",dp[a[2]][a[1]][a[0]] );

    return 0;
}

