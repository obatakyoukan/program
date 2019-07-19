#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  2*1e9;


int main(){
    ll N,W;
    cin>>N>>W;
    vector<ll> w(N),v(N);
    for(int i=0;i<N;i++)cin>>w[i]>>v[i];
    vector<ll> dp(N*1000+1, inf);
    dp[0] = 0;
    for(int i=0;i<N;i++){

	for(int j=N*1000;j>=v[i];j--){
	    dp[j] = min(dp[j],dp[j-v[i]] + w[i]);
	}
    }
    int ans = 0;
   // for(int i=0;i<N*100+1;i++)cout<<i<<' '<<dp[i]<<endl;
    for(int i=0;i<N*1000+1;i++)if(dp[i] <=W)ans = i;
    cout<<ans<<endl;
    return 0;
}

