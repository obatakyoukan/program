#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf = 1e12 ;


vector<ll> daikus(vector<vector<mp> > &g,int s){
	int n = g.size();
	vector<ll> res(n,inf);
	priority_queue<mp,vector<mp>,greater<mp> > q;
	q.push(mp(0,s) );
	while(!q.empty()){
	    mp now = q.top();
	    q.pop();
	    ll nn = now.second;
	    ll cost = now.first;
	    if( res[nn] != inf) continue;
	    res[nn] = cost;
	    for(int i=0;i<g[nn].size();i++){
		ll next = g[nn][i].second;
		ll nc = cost + g[nn][i].first;
		if(res[next] != inf ) continue;
		q.push( mp(nc,next) );
	    }
	}
	return res;
}

int main(){
    ll n,m;
    ll sum = 0;
    cin>>n>>m;
    vector<vector<mp> > g( n );
    vector<ll> deg(n,0);
    vector<ll> odds;
    for(int i=0;i<m;i++){
	ll s,t,d;
	cin>>s>>t>>d;
	g[s].push_back(mp(d,t) );
	g[t].push_back(mp(d,s) );
	sum += d;
	deg[s]++;
	deg[t]++;
    }
    for(int i=0;i<n;i++) if( deg[i] %2 == 1) odds.push_back(i);
    int v = odds.size();
    vector<vector<ll> > G(v,vector<ll>(v));
    for(int i=0;i<v;i++){
	vector<ll> tmp = daikus(g,odds[i]);
	for(int j=0;j<v;j++) G[i][j] = tmp[ odds[j] ];
    }

    vector<ll> dp(1<<v,inf);
    dp[0] = 0;
    for(int k = 0;k< (1<<v);k++){
	for(int i=0;i<v;i++){
	    if(k&(1<<i) ) continue;
	    for(int j=i+1;j<v;j++){
		if(k&(1<<j) ) continue;
		dp[ k | (1<<i) | (1<<j) ] = min( dp[ k | (1<<i) | (1<<j)] , dp[k] + G[i][j] ) ;
	    }
	}
    }
    cout<<sum + dp[ (1<<v)-1 ] <<endl;
    return 0;
}

