#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9+7;
vector<vector<ll> > dp,g;
vector<bool> used;
ll dfs( int s ){
    if(used[s]) return 1;
    if(used[s]) return (dp[s][0]+ dp[s][1] ) %mod;
    used[s] = true;
    ll res = 1;
   
    for(int i=0;i<g[s].size();i++){
	ll next = g[s][i];
	if(used[next])continue;
	dp[s][0] *= dfs(next);
	dp[s][0] %= mod;
	dp[s][1] *= dp[next][0];
	dp[s][1] %= mod;
    }
    return (dp[s][0] + dp[s][1] )%mod;
}

int main(){
    int n;
    cin>>n;
    used = vector<bool>(n,false) ;
    g = vector<vector<ll> >(n) ;
    dp = vector<vector<ll> > (n , vector<ll>(2,1 ) );
    for(int i=0;i<n-1;i++){
	int x,y;
	cin>>x>>y;
	x--,y--;
	g[x].push_back(y);
	g[y].push_back(x);
    }
    cout<<dfs(0)<<endl;
    return 0;
}

