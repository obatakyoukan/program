#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

struct Lowlink{//O(v) ??? O(v + e )???
    ll n;
    vector<vector<ll> > g;
    vector< mp > bridge;
    vector< ll > articulation;
    vector< ll > ord , low;
    vector< bool > used;
    Lowlink(){}
    Lowlink( ll n ):n(n){
	g = vector<vector<ll> >(n);
	ord = vector<ll>(n);
	low = vector<ll>(n);
	used = vector<bool>(n,false);
    }
    void add_edge( ll s , ll t ){
	g[s].push_back( t );
	g[t].push_back( s );
    }
    void solve(){
	ll k = 0;
	for(ll i=0;i<n;i++)if( !used[i] )dfs( i , -1 , k );
	sort( bridge.begin(),bridge.end() );
	sort( articulation.begin(),articulation.end() );
    }
    void dfs(ll v, ll p ,ll &k){
	used[v] = true;
	ord[v] = k++;
	low[v] = ord[v];
	bool isarticulation = false;
	ll cnt = 0;
	for(ll i=0;i<g[v].size();i++){
	    if( !used[ g[v][i] ] ){
		cnt++;
		dfs(g[v][i],v,k);
		low[v] = min( low[v] , low[ g[v][i] ] );
		if( ~p && ord[v] <= low[g[v][i]])isarticulation = true;
		if( ord[v] < low[ g[v][i] ] )bridge.push_back( mp( min( v, g[v][i] ) , max( v, g[v][i] ) ) );
	    }else if( g[v][i] != p ){
		low[v] = min( low[v] , ord[ g[v][i] ] );
	    }
	}
	if( p==-1 && cnt > 1 )isarticulation = true;
	if( isarticulation ) articulation.push_back( v );
    }
};

int main(){
    ll v,e;
    cin>>v>>e;
    Lowlink L(v);
    for(ll i=0;i<e;i++){
	ll s,t;
	cin>>s>>t;
	L.add_edge( s,t );
    }
    L.solve();
    for(auto i:L.bridge ){
	cout<<i.first<<' '<<i.second<<endl;
    }
    return 0;
}

