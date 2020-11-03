#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<string,ll> mp;
#define inf 1e9


vector<string> stdaikus(vector<vector<mp> > &g,int s,int t){
	int n = g.size();
	vector<vector<string> > cost(n,vector<string>(n*6+10,"{") );
	vector<vector<bool> > used(n,vector<bool>(n*6+10,false) );
	priority_queue<mp,vector<mp>,greater<mp> > q;
	q.push(mp("",s) );
	cost[s][0] = "";
	while(!q.empty() ){
		mp now = q.top();
		string str = now.first;
		ll nn = now.second;
		q.pop();
		/*if(nn == t){
		    if(str.size() <= (n*6) )return str;
		    else return "NO";
		}*/
		if(str.size() >= n*6+10 ) continue;
		//if(used[nn][str.size() ] )continue;
		//used[nn][str.size()] = true;
		//cost[nn][str.size()] = min(str,cost[nn][str.size()] );
		for(int i=0;i<g[nn].size();i++){
			ll next = g[nn][i].second;
			string nstr =str +  g[nn][i].first;
			if(nstr.size() >= n*6+10 )continue;
			//if(used[next][nstr.size()] )continue;
			if(cost[next][nstr.size()] <= nstr  ) continue;
			cost[next][nstr.size()] = nstr;
			q.push(mp(nstr,next) );
		}
	}
	vector<string> res(n*6+10);
	for(int i=0;i<n*6+10;i++) res[i] = cost[t][i];
	return res;
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
		vector<string> res = stdaikus(g,s,gg);
		bool flag = false;
		string ans1="{",ans2="{";
		for(int i= 0;i<(n-1)*6 + 10;i++){
			ans1 = min(ans1,res[i]);
		}
		for(int i=0;i<=n*6;i++){
			ans2 = min(ans2,res[i]);
		}
		//for(int i=n*6+1;i<n*6+10;i++)cout<<res[i]<<endl;
		if(ans1 == ans2 && ans2.size() <= n*6&& ans1 != "{"){
			cout<<ans1<<endl;
		}else{
			cout<<"NO"<<endl;
		}

	}
	return 0;
}

