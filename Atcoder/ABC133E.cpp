#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9 + 7;
vector<vector<ll> > g;
ll k;
ll dfs(ll now , ll from ){
    ll use_col = k-2;
    if( from == -1 ){
	use_col ++ ;
    }
    if( k < g[now].size() ){
	return 0;
    }
    ll res = 1;
    for( ll i= 0;i<g[now].size();i++){
	if(g[now][i] == from ) continue;
	res *= use_col ;
	res %= mod ;
	use_col--;
	res *= dfs(g[now][i], now);
	res %= mod ;
    }
    return res;
}

int main(){
    ll n;
    cin>>n>>k;
    g = vector<vector<ll> > (n);
    for(int i=0;i<n-1;i++){
	ll a,b;
	cin>>a>>b;
	a--,b--;
	g[a].push_back(b);
	g[b].push_back(a);
    }
    ll r = 0;
    for(int i=0;i<n;i++)if(g[i].size() == 1 ) r = i;
    cout<< ( k *  dfs(r,-1 ) )%mod << endl;
    return 0;
}

