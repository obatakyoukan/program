#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9

vector<ll> daikus(vector<vector<mp> > &g,int s){
	ll v = g.size();
	vector<ll> res(v,inf);
	priority_queue<mp,vector<mp>,greater<mp> > q;
	q.push(mp(0,s) );
	while(!q.empty()){
		mp now = q.top();
		q.pop();
		ll nn = now.second;
		ll cost = now.first;
		if( res[nn] < cost) continue;
		res[nn] = cost;
		for(int i=0;i<g[nn].size();i++){
			ll next = g[nn][i].second;
			ll nc = cost + g[nn][i].first;
			if( res[next] < cost ) continue;
			q.push( mp(nc,next) );
		}
	}
	return res;
}

int main(){
	
    ll v,e,r;
    cin>>v>>e>>r;
    vector<vector<mp> > g(v);
    for(int i=0;i<e;i++){
	ll s,t,d;
	cin>>s>>t>>d;
	g[s].push_back( mp(d,t) );
	//g[t].push_back( mp(d,s) );
    }
    vector<ll> res = daikus(g,r);
    for(int i=0;i<v;i++)if(res[i] == inf) cout<<"INF"<<endl;
    else cout<<res[i]<<endl;
	return 0;
}

