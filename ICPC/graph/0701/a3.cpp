#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
typedef pair<double,ll> dmp;
typedef pair<dmp,mp> mmp;
double inf =1e9;
struct edge{
	int to,d,c;
	edge(){}
	edge(int to,int d,int c):to(to),d(d),c(c){}
};

int main(){
    while(1){
	int n,m,s,t;
	cin>>n>>m;
	if(n==0)break;
	cin>>s>>t;
	s--,t--;
	vector<vector<edge> > g(n);
	for(int i=0;i<m;i++){
		int x,y,d,c;
		cin>>x>>y>>d>>c;
		x--,y--;
		g[x].push_back(edge(y,d,c) );
		g[y].push_back(edge(x,d,c) );
	}
	bool f = true;
	vector<vector<vector<bool> > > used(n,vector<vector<bool> >(n,vector<bool>(31,false) ) );
	priority_queue<mmp,vector<mmp>,greater<mmp> > q;
	q.push( mmp ( dmp( 0.0 , 0 ), mp( s , s )  ) );
	while(!q.empty() ){
	    mmp now = q.top();
	    q.pop();
	    double time = now.first.first;
	    ll speed = now.first.second;
	    ll nn = now.second.first;
	    ll prev = now.second.second;
	    //cout<<nn<<' '<<prev<<' '<<speed<<endl;
	    if( nn == t && speed == 1){
			printf("%0.10lf\n",time);
			f = false;
			break;
	    }
	    //if(used[nn][prev][speed])continue;
	    //used[nn][prev][speed] = true;
	    for(int i=0;i<g[nn].size();i++){
		ll next = g[nn][i].to;
		double dis = g[nn][i].d;
		ll c = g[nn][i].c;
		if(next == prev) continue;
		for(int j=-1;j<=1;j++){
			ll nspeed = speed + j;
			if( nspeed <= 0 || c < nspeed )continue;
			if( used[next][nn][nspeed] ) continue;
			used[next][nn][nspeed] = true;
			q.push( mmp( dmp( time + dis/nspeed , nspeed ) , mp(next,nn )  )  );
		}

	    }
	}
	if(f)cout<<"unreachable"<<endl;

    }	
	return 0;
}

