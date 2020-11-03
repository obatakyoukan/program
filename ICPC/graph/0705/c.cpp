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

int main(){
    ll n;
    cin>>n;
    set<ll> st;
    vector<mp> a(n);
    for(int i=0;i<n;i++){
	cin>>a[i].first>>a[i].second;
	st.insert(a[i].first);
	st.insert(a[i].second);
    }
    ll m = st.size();
    map<ll,ll> tt;
    int id = 0;
    for(auto it:st) tt[it] = id,id++;
    Flow f( n + m + 2 );   // 各積み木　から　横の長さ　に　コスト高さのパスをはる
    ll s = n + m ,t = n + m + 1;
    for(ll i=0;i<n;i++) f.add_edge(s,i,1,0),f.add_edge(i,t,1,0);//souce から　各積み木　へ　, さらに各積み木を選ばないときのsinkへのパス
    for(ll i=0;i<m;i++) f.add_edge(n+i,t,1,0);
    for(ll i=0;i<n;i++){
	f.add_edge(i, n+tt[a[i].first] , 1 , -a[i].second );
	f.add_edge(i, n+tt[a[i].second], 1 , -a[i].first  );
    }
    cout<<-f.fast_mincost_flow(s,t,n)<<endl;

    return 0;
}

