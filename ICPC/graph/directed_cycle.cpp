#include<bits/stdc++.h>
using namespace std;
//
bool dfs(vector<vector<int> > &g,vector<bool> &used,vector<bool> &use,int now){
	if(!used[now]) return false;
	used[now] = false;
	//use[now] = false;
	bool flag = true;
	for(int i=0;i<g[now].size();i++)if(flag){
		int next = g[now][i];
		if(!use[now]) continue;
		flag = dfs(g,used,use,next);
	}
	use[now] = false;
	used[now] = true;
	return flag;
}

int main(){
	int v,e;
	cin>>v>>e;
	vector<vector<int> > g(v);
	for(int i=0;i<e;i++){
		int s,t;
		cin>>s>>t;
		g[s].push_back(t);
	}
	vector<bool> used(v,true);
	vector<bool> use(v,true);
	bool f = true;
	for(int i=0;i<v;i++){
		if(f&&use[i]){
			f = dfs(g,used,use,i);
		}
	}
	if(!f){
		cout<<1<<endl;
	}else{
		cout<<0<<endl;
	}

	return 0;
}

