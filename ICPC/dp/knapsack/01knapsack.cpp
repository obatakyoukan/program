#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9


int main(){
    int N,W;
    cin>>N>>W;
    vector<int> v(N);
    vector<int> w(N);
    for(int i=0;i<N;i++){
	cin>>v[i]>>w[i];
    }
    vector<vector<int> > dp(2,vector<int>(W+1,-inf) );
    dp[0][0] = 0;
    for(int i=0;i<N;i++){
	for(int j=0;j<=W;j++){
	    if( w[i] <= j){
		dp[(i+1)%2][j] = max(dp[i%2][j],dp[i%2][j-w[i]] + v[i]);
	    }else{
		dp[(i+1)%2][j] = dp[i%2][j];
	    }
	}
    }
    int res = 0;
    for(int i=0;i<=W;i++)res = max(res,dp[N%2][i]);
    cout<<res<<endl;
    return 0;
}

