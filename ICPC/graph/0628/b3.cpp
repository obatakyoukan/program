#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<string,ll> mp;
#define inf 1e9


string stdaikus(vector<vector<mp> > &g,int s,int t){
	int n = g.size();
	vector<vector<string> > cost(n,vector<string>(2*n*6+10,"{") );
	vector<vector<bool> > used(n,vector<bool>(2*n*6+10,false) );
	priority_queue<mp,vector<mp>,greater<mp> > q;
	q.push(mp("",s) );
	cost[s][0] = "";
	while(!q.empty() ){
		mp now = q.top();
		string str = now.first;
		ll nn = now.second;
		q.pop();
		//if(str.size() > n*6 ) "NO";
		if(nn == t){
		    if(str.size() <= (n*6) )return str;
		    else return "NO";
		}
		if(used[nn][str.size() ] )continue;
		used[nn][str.size()] = true;
		cost[nn][str.size()] = min(str,cost[nn][str.size()] );
		for(int i=0;i<g[nn].size();i++){
			ll next = g[nn][i].second;
			string nstr =str +  g[nn][i].first;
			if(nstr.size() >= 2*n*6+10 )continue;
			if(used[next][nstr.size()] )continue;
			//if(cost[next][nstr.size()] <= nstr  ) continue;
			//cost[next][nstr.size()] = nstr;
			q.push(mp(nstr,next) );
		}
	}
	return "NO";
}


int main(){
	while(1){
		int n,a,s,gg;
		cin>>n>>a>>s>>gg;
		if(n==0)break;
	//	cout<<"OK"<<n<<' '<<a<<' '<<s<<' '<<gg<<endl;
		vector<vector<mp> > g(n);
		for(int i=0;i<a;i++){
			int x,y;
			string st;
			cin>>x>>y>>st;
			g[x].push_back(mp(st,y) );
		}
		cout<< stdaikus(g,s,gg) <<endl;

	}
	return 0;
}

