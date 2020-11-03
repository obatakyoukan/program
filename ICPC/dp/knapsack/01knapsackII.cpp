#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  2*1e9;

int main(){
    int N,W;
    cin>>N>>W;
    int VM = 100*N+1;
    vector<vector<int> > dp(N+1,vector<int>(VM,inf) );
    dp[0][0] = 0;
    int res = 0;
    vector<int> v(N),w(N);
    for(int i=0;i<N;i++)cin>>v[i]>>w[i];
    for(int i=0;i<N;i++){
	for(int j=0;j<VM;j++){
	    if( v[i] <= j ){
		dp[i+1][j] = min(dp[i+1][j] , dp[i][j-v[i]] + w[i] );
	    }
	    dp[i+1][j] = min(dp[i+1][j],dp[i][j]) ;
	}
    }
    for(int i=0;i<VM;i++) if( dp[N][i] <= W ) res = max(res,i);
    cout<<res<<endl;
    return 0;
}

