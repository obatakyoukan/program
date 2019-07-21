#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9 + 7;

int main(){
    int n,k;
    cin>>n>>k;
    vector<ll> a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    vector<vector<ll> > dp(n+1,vector<ll>(k+1,0) );
    dp[0][k] = 1;
    for(int i=0;i<n;i++){
	ll sum = 0;
	for(int j=0;j<=a[i];j++){
	    sum += dp[i][k-j];
	    sum %= mod;
	    dp[i+1][k-j] = sum;
	}
	for(int j=a[i]+1;j<=k;j++){
	    sum += dp[i][k-j];
	    sum -= dp[i][k-(j-a[i]-1)];
	    sum += mod;
	    sum %= mod;
	    dp[i+1][k-j] = sum;
	}
    }
    cout<<dp[n][0]<<endl;
 //   for(int i=0;i<=n;i++){
//	for(int j=0;j<=k;j++)cout<<dp[i][j]<<' ';
//	cout<<endl;
  //  }

    return 0;
}

