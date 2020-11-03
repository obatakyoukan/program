#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e12


int main(){
	int v,e;
	cin>>v>>e;
	vector<vector<ll> > g(v,vector<ll>(v,inf) );
	for(int i=0;i<e;i++){
		int s,t,w;
		cin>>s>>t>>w;
		g[s][t] = w;
	}
	for(int i=0;i<v;i++)g[i][i] = 0;
	for(int k=0;k<v;k++){
		for(int i=0;i<v;i++){
			for(int j=0;j<v;j++){
			    if(g[i][k] == inf || g[k][j] == inf)continue;
			    g[i][j] = min(g[i][j],g[i][k] + g[k][j] );
			}
		}
	}
	bool negative_cycle = false;
	for(int i=0;i<v;i++) if(g[i][i] != 0) negative_cycle = true;
	if(negative_cycle){
		cout<<"NEGATIVE CYCLE"<<endl;
	}else
	for(int i=0;i<v;i++){
		for(int j=0;j<v;j++){
			if(j!=0)cout<<" ";
			if(g[i][j] == inf)cout<<"INF";
			else cout<<g[i][j];
		}
		cout<<endl;
	}


	return 0;
}

