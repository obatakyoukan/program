#include<bits/stdc++.h>
using namespace std;

//Chu_Liu_Edmonds
typedef pair<int,int> point;
typedef pair<int,point> edge;

#define inf 1e9

int solve(vector<edge> &g,int v,int r){
	vector<point> mins(v,point(inf,-1));
	for(int i=0;i<g.size();i++){
		edge tmp = g[i];
		point p = tmp.second;
		mins[p.second]  =  min(mins[p.second],point(tmp.first,p.first));
	}
	mins[r] = point(-1,-1);	
	vector<int> grop(v,0);
	vector<bool> cycle(v,false);
	int cnt=0;
	
	vector<bool> used(v,false);
	for(int i=0;i<v;i++){
		if(used[i])continue;
		vector<int> chain;
		int now = i;
		while(now !=-1&&!used[now]){
			//元を辿る
			used[now]= true;
			chain.push_back(now);
			now = mins[now].second;
		}
		if(now !=-1){
			bool incycle = false;
			for(int j=0;j<chain.size();j++){
				grop[chain[j]]=cnt;
				if(chain[j]==now){
					cycle[cnt] = true;
					incycle = true;
				}
				if(!incycle)cnt++;
			}
		 if(incycle)cnt++;
		}else{
			for(int j=0;j<chain.size();j++){
					grop[chain[j]] = cnt;
					cnt++;
			}	
		}

	}
	if(cnt==v){
		//because root is -1 
		int ans =1;
		for(int i=0;i<v;i++)ans+=mins[i].first;
		return ans;
	}
	int res = 0;
	for(int i=0;i<v;i++){
		if(i != r && cycle[grop[i]])res += mins[i].first;
	}
	//cycle exist ,so make new graph
	vector<edge> newg;
	for(int i=0;i<g.size();i++){
		edge e = g[i];
		point p = e.second;
		int to = p.second;
		int gfrom = grop[p.first];
		int gto = grop[p.second];
		if(gfrom ==gto)continue;
		else if(cycle[gto])	newg.push_back(edge(e.first-mins[to].first,point(gfrom,gto)) );
		else 	newg.push_back(edge(e.first,point(gfrom,gto) ) );
	}
	return res + solve(newg,cnt,grop[r]);
}


int main(){
	int v,e,r;
	cin>>v>>e>>r;
	vector<edge> g;
	for(int i=0;i<e;i++){
		int s,t,w;
		cin>>s>>t>>w;
		point p = point(s,t);
		g.push_back( edge(w,p) );
	}
	cout<<solve(g,v,r)<<endl;
	return 0;
}
