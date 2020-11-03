#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9


int main(){
    int n,m;
    cin>>n>>m;
    vector<int> dp(n+1,inf);
    dp[0] = 0;
    vector<int> c(m);
    for(int i=0;i<m;i++){
	cin>>c[i];
    }
    for(int i=0;i<m;i++){
	for(int j=0;j<=n;j++){
	    if(  c[i] <= j ){
		dp[j] = min(dp[j],dp[j-c[i]]+1);
	    }
	}
    }
    cout<<dp[n] <<endl;

	return 0;
}

