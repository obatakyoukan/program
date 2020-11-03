#include<bits/stdc++.h>
using namespace std;
// 関節点、橋、lowlink
// lowlink
typedef pair<int,int> mypair;
void dfs(int v,int p,int &k,vector<int> &ord,vector<int> &low,vector<bool> &used,vector<vector<int> > &g,vector<mypair> &bridge,vector<int> &articulation){
	used[v] = true;
	ord[v] = k++;
	low[v] = ord[v];
	bool isarticulation = false;
	int cnt = 0;
	for(int i=0;i<g[v].size();i++){
		if(!used[g[v][i]]){
			cnt++;
			dfs(g[v][i],v,k,ord,low,used,g,bridge,articulation);
			low[v] = min(low[v],low[g[v][i]]);
			if(~p&&ord[v]<=low[g[v][i]])isarticulation = true;
			if(ord[v]<low[g[v][i]])bridge.push_back( mypair( min(v,g[v][i]), max(v,g[v][i]) ) ) ;
		}
		else if(g[v][i] != p){
			low[v] = min(low[v],ord[g[v][i]]);
		}
	}
	if(p==-1 &&cnt>1)isarticulation=true;
	if(isarticulation)articulation.push_back(v);
}

int main(){
	int v,e;
	cin>>v>>e;
	vector<vector<int> >g(v);
	vector<int> ord(v),low(v);
	vector<int> art;
	vector<mypair> bridge;
	vector<bool> used(v,false);
	int k=0;

	for(int i=0;i<e;i++){
	int s,t;
	cin>>s>>t;
	g[s].push_back(t);
	g[t].push_back(s);
	}

	for(int i=0;i<v;i++)if(!used[i])dfs(i,-1,k,ord,low,used,g,bridge,art);
	sort(art.begin(),art.end());
	sort(bridge.begin(),bridge.end());
	//関節点
	//cout<<art.size()<<endl;
	//for(int i=0;i<art.size();i++)cout<<art[i]<<endl;	
	//橋
	//cout<<bridge.size()<<endl;
	for(int i=0;i<bridge.size();i++)cout<<bridge[i].first<<' '<<bridge[i].second<<endl;
	return 0;
}

