#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e12;


int main(){
    int n;
    cin>>n;
    vector<ll> a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    vector<vector<ll> > dp(n+1,vector<ll>(n+1,0) );//[i,j)での再全解
    for(int i=1;i<=n;i++){
	for(int j=0; i+j<=n;j++){
	    int k = i+j;
	    if( (n-i)%2 == 0){//先手
		dp[j][k] = max( dp[j+1][k] + a[j], dp[j][k-1] + a[k-1] );
	    }else{//後手
		dp[j][k] = min( dp[j+1][k] - a[j], dp[j][k-1] - a[k-1] );
	    }
	}
    }
    cout<<dp[0][n]<<endl;
    return 0;
}

