#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9+7;

int main(){
    string s;
    ll d ;
    cin>>s>>d;
    ll n = s.size();
    vector<ll> k(n);
    for(int i=0;i<n;i++) k[i] = s[i]-'0';
    vector<vector<vector<ll> > > dp(n+1,vector<vector<ll> >(d,vector<ll>(2,0) ) );
    dp[0][0][0] = 1;
    for(int i=0;i<n;i++){
	for(int j=0;j<d;j++){
	    for(int l=0;l<10;l++) dp[i+1][(j+l)%d][1] += dp[i][j][1],dp[i+1][(j+l)%d][1]%=mod;
	    for(int l=0;l<k[i];l++) dp[i+1][(j+l)%d][1] += dp[i][j][0],dp[i+1][(j+l)%d][1]%=mod;
	    dp[i+1][(j+k[i])%d][0] += dp[i][j][0];
	    dp[i+1][(j+k[i])%d][0] %= mod;
	}
    }
    cout<<(dp[n][0][0] + dp[n][0][1] -1 + mod )%mod <<endl;
    return 0;
}

