#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9

struct LCA{//lowest common ancestor
	int MAX_LOG_V = 50;
	vector<vector<int> > g;
	vector<vector<int> > parent;
	int root = 0,V;
	vector<int> depth;
	LCA(){}
	LCA(int V):V(V){init();}
	void init(){
		for(int i=0;i<g.size();i++)g[i].clear();
		g.clear();
		for(int i=0;i<parent.size();i++)parent[i].clear();
		parent.clear();
		depth.clear();
		g.resize(V);
		parent.resize(MAX_LOG_V,vector<int>(V) );
		depth.resize(V);
	}
	void dfs(int v,int p,int d){
		parent[0][v] = p;
		depth[v] = d;
		for(int i=0;i<g[v].size();i++)if(g[v][i] != p) dfs(g[v][i],v,d+1);
	}
	void construct(){
		dfs(root,-1,0);
		for(int k=0;k+1<MAX_LOG_V;k++)
		    for(int i=0;i<V;i++)
			if(parent[k][i]<0) parent[k+1][i] = -1;
			else parent[k+1][i] = parent[k][parent[k][i]];
	}
	int lca(int u,int v){
		if(depth[u] > depth[v]) swap(u,v);
		for(int k=0;k<MAX_LOG_V;k++)
		    if( (depth[v]-depth[u]) >> k&1)
			v = parent[k][v];
		if(u==v) return u;
		for(int k=MAX_LOG_V-1;k>=0;k--)
		    if(parent[k][u] != parent[k][v]){
			u = parent[k][u];
			v = parent[k][v];
		    }
		return parent[0][u];
	}
	void add_edge(int u,int v){ 
	    g[u].push_back(v);
	    g[v].push_back(u);
	}
};

int main(){
	int n;
	cin>>n;
	LCA t(n);
	for(int i=0;i<n;i++){
		int k;
		cin>>k;
		for(int j=0;j<k;j++){
			int c;
			cin>>c;
			t.add_edge(i,c);
		}
	}
	t.construct();
	int q;
	cin>>q;
	for(int i=0;i<q;i++){
		int u,v;
		cin>>u>>v;
		cout<<t.lca(u,v)<<endl;
	}
	return 0;
}

