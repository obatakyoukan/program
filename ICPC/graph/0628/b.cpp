#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<string,ll> mp;
#define inf 1e9


string stdaikus(vector<vector<mp> > &g,int s,int t){
	int n = g.size();
	char z = 'z' + 1;
	string zz ;zz[0]= z;
	vector<string> cost(n,zz);
	priority_queue<mp,vector<mp>,greater<mp> > q;


	string res ;
	return res;
}

vector<string> cost;
bool bellman_ford(vector<vector<mp> > &g,int s ){
   	int n = g.size();
	string zz = "zzzzzzzzzz";
	//cout<<"ok"<<endl;
	cost = vector<string> (n,zz);
	cost[s] = "";
	for(int i=0;i<n;i++){
		for(int v=0;v<n;v++){
			for(int k=0;k<g[v].size();k++){
				//cout<<i<<' '<<v<<' '<<k<<endl;
				mp e = g[v][k];
				string tmp = cost[v] + e.first;
				//cout<<i<<' '<<v<<' '<<e.second<<' '<<tmp<<endl;
				if(cost[v] != zz && cost[e.second] > tmp){
				    cost[e.second] = tmp;
				    cout<<i<<' '<<n<<endl;
				    if(i==n-1)return true;
				}
			}
		}
	}
	return false;
}

int main(){
	while(1){
		int n,a,s,gg;
		cin>>n>>a>>s>>gg;
		if(n==0)break;
		vector<vector<mp> > g(n);
		for(int i=0;i<a;i++){
			int x,y;
			string st;
			cin>>x>>y>>st;
			g[x].push_back(mp(st,y) );
		}
		bool f = bellman_ford(g,s);
		//cout<<"end"<<endl;
		//for(int i=0;i<cost.size();i++)cout<<i<<' '<<cost[i]<<endl;
		if(f){
			cout<<"NO"<<endl;
		}else{
			cout<<cost[gg]<<endl;
		}
	}
	return 0;
}

