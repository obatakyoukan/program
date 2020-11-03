#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
double  inf = 1e9;
typedef pair<double,mp> mmp;

int main(){
    while(1){
	ll n,m,p,a,b;
	cin>>n>>m>>p>>a>>b;
	if(n==0)break;
	a--,b--;
	vector<vector<mp> > g(m);
	vector<ll> t(n);
	for(int i=0;i<n;i++)cin>>t[i];
	for(int i=0;i<p;i++){
		ll x,y,z;
		cin>>x>>y>>z;
		x--,y--;
		g[x].push_back(mp(z,y) );
		g[y].push_back(mp(z,x) );
	}
	//vector<vector<double> > dp( m,vector<double>( 1<<n , inf) );
	vector<vector<bool> > used( m,vector<bool>( 1<<n , false ) );
	priority_queue< mmp,vector<mmp> ,greater<mmp> > q;
	q.push( mmp(0.0, mp(0,a) ) );
	bool f = true;
	while(!q.empty() ){
		mmp now = q.top();
		q.pop();
		ll nn = now.second.second;
		ll tt = now.second.first;
		double time = now.first;
		if( nn == b){
			printf("%0.10lf\n",time);
			f = false;
			break;
		}
		if( used[nn][tt] ) continue;
		used[nn][tt] = true;
		//if( dp[nn][tt] <= time ) continue;
		//dp[nn][tt] = time;
		for(int i=0;i<g[nn].size();i++){
		    ll next = g[nn][i].second;
		    double dis = g[nn][i].first;
		    for(int j=0;j<n;j++){
			if( (tt>>j) & 1 ) continue;
			if( used[next][ tt | (1<<j) ] ) continue;
			q.push( mmp( time + dis/t[j] , mp( (tt|(1<<j) ) , next  ) )  );

		    }
		}
	}
	if(f){
		cout<<"Impossible"<<endl;
	}

    }
	return 0;
}

