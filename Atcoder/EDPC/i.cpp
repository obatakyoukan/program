#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int n;
    cin>>n;
    vector<double> p(n);
    for(int i=0;i<n;i++)cin>>p[i];
    vector<vector<double> > dp(n+1,vector<double>(n+1,0) );
    dp[0][0] = 1;
    for(int i=0;i<n;i++){
	dp[i+1][0] = dp[i][0] * (1-p[i]);
	for(int j=0;j<n;j++){
	    dp[i+1][j+1] = dp[i][j] * p[i] + dp[i][j+1] * ( 1-p[i] );
	}
    }
    double res = 0;
    for(int i=n/2 + 1;i<=n;i++) res += dp[n][i];
    printf("%0.10lf\n",res);
    return 0;
}

