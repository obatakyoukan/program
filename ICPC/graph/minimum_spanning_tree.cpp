#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9


int main(){
	int v,e;
	cin>>v>>e;
	vector<vector<mp> > g(v);
	for(int i=0;i<e;i++){
		int s,t,d;
		cin>>s>>t>>d;
		g[s].push_back(mp(d,t) );
		g[t].push_back(mp(d,s) );
	}
	vector<bool > used(v,false);
	used[0] = true;
	priority_queue<mp,vector<mp>,greater<mp> > q;
	for(int i=0;i<g[0].size();i++)q.push( g[0][i] );
	ll ans =0;
	while(!q.empty() ){
		mp now = q.top();
		q.pop();
		ll nn = now.second;
		ll cost = now.first;
		if(used[nn])continue;
		ans += cost;
		used[nn] = true;
		for(int i=0;i<g[nn].size();i++){
			q.push(g[nn][i]);
		}
	}
	cout<<ans<<endl;
	return 0;
}

