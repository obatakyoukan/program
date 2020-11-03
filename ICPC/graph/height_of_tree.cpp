#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9


vector<int> daikus(vector<vector<mp> > &g,int s){
	int n = g.size();
	vector<bool> used(n,false);
	vector<int> res(n,inf) ;
	priority_queue<mp,vector<mp> ,greater<mp> > q;
	q.push(mp(0,s) );
	while(!q.empty() ){
		mp now = q.top();
		q.pop();
		int nn = now.second;
		int cost = now.first;
		if(used[nn])continue;
		used[nn] = true;
		res[nn] = cost;
		for(int i=0;i<g[nn].size();i++){
		    int next  = g[nn][i].second;
		    int nc = g[nn][i].first + cost;
		    if(used[next])continue;
		    q.push(mp(nc,next) );
		}
	}
	return res;
}

vector<int> height(vector<vector<mp> > &g){
	int n = g.size();
    	vector<int> v,v1,v2,res(n);
	v = daikus(g,0);
	int p1 = max_element(v.begin(),v.end()) -v.begin();
	v1 = daikus(g,p1);
	int p2 = max_element(v1.begin(),v1.end())-v1.begin();
	v2 = daikus(g,p2);
	for(int i=0;i<n;i++)res[i] = max(v1[i],v2[i]);
	return res;
}

int main(){
	int n;
	cin>>n;
	vector<vector<mp> > g(n);
	for(int i=0;i<n-1;i++){
		int s,t,w;
		cin>>s>>t>>w;
		g[s].push_back(mp(w,t) );
		g[t].push_back(mp(w,s) );
	}
	vector<int> res = height(g);
	for(int i=0;i<n;i++)cout<<res[i]<<endl;


	return 0;
}

