#include<bits/stdc++.h>
#define INF 1e9
using namespace std;
	typedef struct edge{
	int to,cap,rev;
	}edge;
void add_edge(int from,int to,int cap,vector<vector<edge> > &g){
	edge f,t;
	f = (edge){to,cap,(int)g[to].size()};
	g[from].push_back(f);
	t = (edge){from,0,(int)g[from].size()-1};
	g[to].push_back(t);
}
int dfs(int v,int t,int f,vector<vector<edge> > &g,vector<bool> &used){
	if(v==t)return f;
	used[v] = true;
	for(int i=0;i<g[v].size();i++){
		edge &e = g[v][i];
		if(!used[e.to]&&e.cap>0){
			int d = dfs(e.to,t,min(f,e.cap),g,used);
			if(d>0){
				e.cap -=d;
				g[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s,int t,vector<vector<edge> > &g){
	int flow=0;
	while(1){
		vector<bool>  used(g.size(),false);
		int f = dfs(s,t,INF,g,used);
		if(f==0) return flow;
		flow+=f;
	}
}

int main(){
	int v,e;
	cin>>v>>e;
	vector<vector<edge> > g(v);
	for(int i=0;i<e;i++){
	int a,b,c;
	cin>>a>>b>>c;
	add_edge(a,b,c,g);
	}
	cout<<max_flow(0,v-1,g)<<endl;
	return 0;
}

