#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9+7;

int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<ll> sum(n+3,0);
    vector<vector<ll> > dp(n+1,vector<ll>(n+3,0) );
    for(int i=0;i<=n;i++)dp[1][i] = 1;
    for(int i=2;i<=n;i++){
	sum[0] = 0;
	for(int j=1;j<n-i+3;j++) sum[j] = (sum[j-1] + dp[i-1][j-1] )% mod;
	if(s[i-2]=='<'){
	   // for(int j=0;j<n-i+1;j++)for(int k=j+1;k<n-i+2;k++)dp[i][j]=(dp[i][j]+dp[i-1][k])%mod;
	    for(int j=0;j<n-i+1;j++) dp[i][j] = (sum[n-i+2] - sum[j+1] + mod ) %mod;
	}else{
	   // for(int j=0;j<n-i+1;j++)for(int k=0;k<j+1;k++)dp[i][j]=(dp[i][j]+dp[i-1][k])%mod;
	    for(int j=0;j<n-i+1;j++) dp[i][j]  = sum[j+1];
	}
    }
    cout<<dp[n][0]<<endl;
    return 0;
}

