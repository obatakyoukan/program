#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9

vector<ll> daikus(vector<vector<mp> > &g, ll s){
	ll n = g.size();
	vector<bool> used(n,false);
	vector<ll> c(n,inf);
	priority_queue<mp,vector<mp>,greater<mp> > q;
	q.push(mp(0,s) );
	while(!q.empty()){
		mp now = q.top();
		q.pop();
		ll nn = now.second;
		ll cost = now.first;
		if(used[nn])continue;
		//cout<<s<<' '<<nn<<' '<<cost<<endl;
		used[nn] = true;
		c[nn] = cost;
		for(int i=0;i<g[nn].size();i++){
			ll next = g[nn][i].second;
			ll nc = g[nn][i].first;
			if(used[next])continue;
			q.push(mp(cost+nc,next) );
		}
	}

	return c;
}


int main(){
    while(1){
	int n;
	cin>>n;
	if(n==0)break;
	vector<ll> p(n-1);
	vector<ll> d(n-1);
	vector<ll> deg(n,0);
	ll sum = 0;
	for(int i=0;i<n-1;i++)cin>>p[i];
	for(int i=0;i<n-1;i++)cin>>d[i];
	vector<vector<mp> > g(n);
	for(int i=0;i<n-1;i++){
		p[i]--;
		deg[i+1]++;
		deg[p[i]]++;
		g[i+1].push_back(mp(d[i],p[i]) );
		g[p[i]].push_back(mp(d[i],i+1) );
		sum += d[i];
	}
	/*for(int i=0;i<n;i++)cout<<deg[i]<<endl;
	for(int i=0;i<n;i++){
		cout<<"index "<<i<<": ";
		for(int j=0;j<g[i].size();j++)cout<<g[i][j].second<<' ';
		cout<<endl;
	}*/
	for(int i=0;i<n;i++) if(deg[i]!= 1){
		for(int j=0;j<g[i].size();j++){
			if(deg[g[i][j].second] != 1){
			    //cout<<i<<' '<<j<<' '<<g[i][j].first<<endl;
			    sum += g[i][j].first;
			}
		}
	}
	//cout<<"OK"<<endl;
	vector<vector<ll> > A(n);
	for(int i=0;i<n;i++)A[i] = daikus(g,i);
	//cout<<"NONO"<<endl;
	ll m = 0;
	for(int i=0;i<n;i++){
	    	if(deg[i]==1)continue;
		for(int j=0;j<n;j++){
		    if(deg[j]==1)continue;
			m = max(m,A[i][j]);
		}
	}
	//cout<<sum<<endl;
	//cout<<m<<endl;
	cout<<sum-m<<endl;
    }
	return 0;
}

