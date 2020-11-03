#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<string,ll> mp;
#define inf 1e9


int main(){
	while(1){
	    int n,a,s,t;
	    cin>>n>>a>>s>>t;
	    //cout<<"Case: "<<n<<endl;
	    if(n==0)break;
	    vector<vector<mp> > g(n);
	    for(int i=0;i<a;i++){
		string s;
		int x,y;
		cin>>x>>y>>s;
		g[x].push_back(mp(s,y) );
	    }
	    priority_queue<mp,vector<mp>,greater<mp> > q;
	    vector<vector<string> > d(n,vector<string>(2*n*6,"{") );
	    q.push(mp("",s) );
	    d[s][0] = "";
	    bool f = true;
	    while(!q.empty()){
		mp now = q.top();
		q.pop();
		int nn = now.second;
		string nowstr = now.first;
		if(nn== t){
			if(nowstr.size() > n*6 ) {
				cout<<"NO"<<endl;
			}else{
				cout<<nowstr<<endl;
			}
			f = false;
			break;
		}
		if(d[nn][nowstr.size()] <nowstr)continue; 
		for(int i=0;i<g[nn].size();i++){
			mp e = g[nn][i];
			string nextstr = nowstr + e.first;
			if(nextstr.size() >= 2*n*6 )continue;
			if(d[e.second][nextstr.size()] > nextstr){
				d[e.second][nextstr.size()] = nextstr;
				q.push(mp(nextstr,e.second) );
			}
		}
	    }
	    if(f)cout<<"NO"<<endl;
	}
	return 0;
}

