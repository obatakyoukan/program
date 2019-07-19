#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e12;


int main(){

    int N,W;
    cin>>N>>W;
    vector<ll> v(N),w(N);
    for(int i=0;i<N;i++)cin>>w[i]>>v[i];
    vector<vector<ll> > dp(2,vector<ll>(W+1,0) );
    dp[0][0] = 0;
    for(int i=0;i<N;i++){
	for(int j=W;j>=w[i];j--){
	    dp[(i+1)%2][j] = max( dp[i%2][j] , dp[i%2][j-w[i]] + v[i] );
	}
	for(int j=0;j<w[i];j++) dp[(i+1)%2][j] = dp[i%2][j]; 
    }
    cout<<dp[N%2][W]<<endl;

    return 0;
}

