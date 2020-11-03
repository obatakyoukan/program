#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9

struct edge{
    ll to,cap,cost,rev;
    edge(){}
    edge(ll to,ll cap,ll rev):to(to),cap(cap),rev(rev){}
    edge(ll to,ll cap,ll cost,ll rev):to(to),cap(cap),cost(cost),rev(rev){}
};

typedef vector<vector<edge> > graph;
struct Dinic{
    ll n;
    graph g;
    vector<ll> level,iter;
    Dinic() {}
    Dinic(ll n): n(n){
	g.resize(n);
	level.resize(n);
	iter.resize(n);
    }
    void add_edge(ll from, ll to, ll cost){
	g[from].push_back(edge(to,cost,g[to].size()   ) );
	g[to].push_back(edge(from,0,g[from].size() -1 ) );
    }
    void bfs(ll s){
	fill(level.begin(),level.end(),-1);
	queue<ll> q;
	q.push(s);
	level[s] = 0;
	while(!q.empty()){
	    ll tmp = q.front();
	    q.pop();
	    for(ll i=0;i<g[tmp].size();i++){
		edge &e = g[tmp][i];
		if(e.cap > 0 && level[e.to] < 0){
		    level[e.to] = level[tmp] + 1;
		    q.push(e.to);
		}
	    }
	}
    }
    ll dfs(ll v,ll t,ll f){
	if( v == t ) return f;
	for(ll &i = iter[v]; i < g[v].size() ; i++){
	    edge &e = g[v][i];
	    if( e.cap > 0 && level[v] < level[e.to] ){
		ll d = dfs(e.to, t, min(f,e.cap) );
		if( d > 0 ){
		    e.cap -= d;
		    g[e.to][e.rev].cap += d;
		    return d;
		}
	    }
	}
	return 0;
    }
    ll max_flow(ll s,ll t){
	ll flow = 0, f;
	while(1){
	    bfs(s);
	    if(level[t] < 0) return flow;
	    fill(iter.begin(),iter.end() , 0);
	    for(f = dfs(s,t,inf); f > 0; f = dfs(s,t,inf) ) flow += f;
	}
    }
};



int main(){
    ll x,y,e;
    cin>>x>>y>>e;
    ll S = x + y;
    ll T = x + y + 1;
    Dinic f(x+y+2);
    for(int i=0;i<x;i++)f.add_edge(S,i,1);// sorce から　Xの集合へ
    for(int i=0;i<y;i++)f.add_edge(x+i,T,1);// Yの集合からsinkへ
    for(ll i=0;i<e;i++){
	ll s,t;
	cin>>s>>t;
	f.add_edge(s,x+t,1);// X to Y
    }
    cout<<f.max_flow(S,T)<<endl;
    return 0;
}

