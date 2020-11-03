#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define INF 1e9
struct edge{
    ll to,rev;
    ll cap,cost;
    edge(ll to, ll cap ,ll rev):to(to),cap(cap),rev(rev){}
    edge(ll to, ll cap,ll cost,ll rev):to(to),cap(cap),cost(cost),rev(rev){}
};
typedef vector<vector<edge> > graph;
struct Flow{
	graph g;
	ll MAXC = 1<<30;
	ll n;
	vector<bool> used;
	vector<ll> prevv,preve,dist;
	Flow() {} 
	Flow(ll _n) : g(_n),n(_n),used(_n,false),prevv(_n),preve(_n),dist(_n,MAXC){}
	// G[e.to][e.rev] で逆辺を操作できる
	void add_edge(ll from , ll to , ll cap){
	    g[from].push_back( edge(to,cap,g[to].size() ) );
	    g[to].push_back( edge(from,0,g[from].size()-1) );
	}
	void add_edge(ll from, ll to, ll cap,ll cost){
	    g[from].push_back( edge(to,cap,cost,g[to].size() ) );
	    g[to].push_back( edge(from, 0,-cost,g[from].size()-1) );
	}
	// Ford-Fulkerson 法による 最大流 O( F |E| )
	// Bellman-Ford 法による 最小費用流 O( F |V| |E| )
	// Verified: AOJ GRL_6_A (Maximum Flow)
	// 行き先と容量と逆辺のインデックスを記録する構造体
	// 通常のグラフの辺の構造体と異なるため注意
	// 最小費用流はもう少し速くできるので、改良しましょう
	// → ダイクストラが使えるようにポテンシャルを導入しよう
	ll dfs(ll v,ll t , ll f){
	    if( v== t)return f;
	    used[v] = true;
	    for(int i=0;i< g[v].size();i++){
		edge &e = g[v][i];
		if(!used[e.to] && e.cap > 0){
		    ll d = dfs(e.to,t,min(f,e.cap) );
		    if( d > 0){
			e.cap -= d;
			g[e.to][e.rev].cap  += d;
			return d;
		    }
		}
	    }
	    return 0;
	}
	ll max_flow(ll s,ll t){
	    ll flow = 0;
	    while(1){
		fill(used.begin(),used.end(),false);
		ll f = dfs(s,t,INF);
		if( f== 0) return flow;
		flow += f;
	    }
	}
	ll mincost_flow(ll s,ll t,ll f){
	    ll res = 0;
	    ll M = MAXC ;
	    while(f>0){
		fill(dist.begin(),dist.end(), M);
		dist[s] = 0;
		bool update = true;
		while(update){
		    update = false;
		    for(ll i=0;i<n;i++){
			if(dist[i] == M) continue;
			for(ll j=0;j<g[i].size();j++){
			    edge &e = g[i][j];
			    if(e.cap > 0 && dist[e.to] > dist[i] + e.cost){
				dist[e.to] = dist[i] + e.cost;
				prevv[e.to] = i;
				preve[e.to] = j;
				update = true;
			    }
			}
		    }
		}
		if( dist[t] == M) return -1;
		ll d = f;
		for(ll i= t ; i!=s; i=prevv[i] ) d = min(d,g[ prevv[i] ][ preve[i] ].cap );
		f -= d;
		res += d*dist[t];
		for(ll i= t ; i!=s; i=prevv[i] ){
		    edge &e = g[prevv[i] ][preve[i]];
		    e.cap -= d;
		    g[i][e.rev].cap += d;
		}
	    }
	    return res;
	}
	 // ポテンシャルの導入により、ダイクストラ法で最小費用流を解く
	 // [仮定している条件]
	 //     1. グラフに負の閉路が存在しない (流量の 0 初期化のため)
	 //        もし存在するならベルマンフォードで負の閉路を見つけ
	 //        そこに流せるだけ流してスタート
	 //     2. グラフに負の辺が存在しない (pot_0 の計算可能性)
	 //     もし存在する場合は最初のみベルマンフォードを使う必要あり
	ll fast_mincost_flow(ll s,ll t,ll f){
	    ll res = 0, M = MAXC;
	    vector<ll> pot(n);
	    while( f > 0 ){
		priority_queue<mp,vector<mp>,greater<mp> > q;
		fill(dist.begin(),dist.end(),M);
		dist[s] = 0;
		q.push( mp(0,s) );
		while(!q.empty()){
		    mp now = q.top();
		    q.pop();
		    ll v = now.second;
		    ll cost = now.first;
		    if( dist[v] < cost ) continue;
		    for(ll i=0;i<g[v].size();i++){
			edge &e = g[v][i];
			if( e.cap > 0 && dist[e.to] > dist[v] + e.cost + pot[v] - pot[e.to] ){
			    dist[e.to] = dist[v] + e.cost + pot[v] - pot[e.to];
			    prevv[e.to] = v;
			    preve[e.to] = i;
			    q.push( mp(dist[e.to],e.to) );
			}
		    }
		}
		if( dist[t] == M ) return -1;
		for(ll i = 0; i< n;i++)pot[i] += dist[i];
		ll d = f;
		for(ll i = t; i!=s; i= prevv[i] ) d = min(d,g[prevv[i]][preve[i]].cap);
		f-=d;
		res += d*pot[t];
		for(ll i = t; i!=s; i=prevv[i] ){
		    edge &e = g[prevv[i] ][preve[i]];
		    e.cap -= d;
		    g[i][e.rev].cap += d;
		}
	    }
	    return res;
	}
};

struct flow_lr{//下限制約付き最大流
    Flow f;
    ll S,T;
    ll sum_lb;
    //ll n,m; //頂点数　辺の数
    flow_lr(){}
    flow_lr(ll n) : f(n+2),S(n),T(n+1),sum_lb(0){}
    //flow_lr(ll n , ll m) : f( n+m+4),S( n+m+2 ),T( n+m+3 ),sum_lb(0),n(n),m(m) {} //???
    void add_edge(ll u,ll v , ll lb, ll ub){
	assert(0 <= lb);
	assert(lb <= ub);
	if( u == v || ub == 0 ) return ;
	f.add_edge(u,v,ub-lb);
	f.add_edge(S,v,lb);
	f.add_edge(u,T,lb);
	sum_lb += lb;
    }

    ll max_flow(ll s,ll t){
	ll S = f.n - 2, T = f.n -1;
	ll a = f.max_flow(S,T);
	ll b = f.max_flow(s,T);
	ll c = f.max_flow(S,t);
	ll d = f.max_flow(s,t);
	return (a + c == sum_lb && a + b == sum_lb ) ? b + d : -1;
    }
};

bool check(ll l,ll r,ll m,ll n, flow_lr f){
    ll S =  m  + n;
    ll T = S+1;
    for(int i=0;i<n;i++)f.add_edge(m+i,T,l,r);
    ll F=f.max_flow(S,T);
    return m==F;
}


int main(){
    ll v,e;
    cin>>v>>e;
    Flow f(v);
    for(ll i=0;i<e;i++){
	ll u,v,c;
	cin>>u>>v>>c;
	f.add_edge(u,v,c);
    }
    cout<<f.max_flow(0,v-1)<<endl;
    return 0;
}

