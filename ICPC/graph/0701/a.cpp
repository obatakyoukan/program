#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,int> mp;
typedef pair<mp,int> mmp;
typedef pair<mmp,int> mpp;
#define inf 1e9


int main(){
	int  n,m,s,gg;
	while(1){
		cin>>n>>m;
		if(n==0)break;
		cin>>s>>gg;
		s--,gg--;
		vector<vector<mmp> > g(n);
		for(int i=0;i<m;i++){
			int x,y,d,c;
			cin>>x>>y>>d>>c;
			x--,y--;
			g[x].push_back(mmp(mp(d,c),y) );
			g[y].push_back(mmp(mp(d,c),x) );
		}
		vector<vector<double> > tt(n,vector<double>(31,(double)inf) );
		priority_queue<mpp,vector<mpp>,greater<mpp> > q;
		q.push(mpp(mmp(mp(0.0,0),s),-1) );
		tt[s][0] = 0.0;
		bool f = true;
		while( !q.empty() ){
			mpp noww = q.top();
			mmp now =  noww.first;
			q.pop();
			double cost = now.first.first;
			int speed = now.first.second;
			int nn = now.second;
			int prev = noww.second;
			if( nn==gg && speed==1){
				printf("%0.10lf\n",cost);
				f = false;
				break;
			}
			for(int i=0;i<g[nn].size();i++){
			    	double d = g[nn][i].first.first;
				int  c = g[nn][i].first.second; 
				int next = g[nn][i].second;
				if(next == prev) continue;
				for(int j=-1;j<2;j++){
				    	int nspeed  = speed + j;
					if( nspeed > c || nspeed <=0) continue;
					if(tt[next][nspeed] != inf )continue;
					tt[next][nspeed] = tt[nn][speed] + d/nspeed;
					q.push(mpp( mmp( mp( tt[next][nspeed] ,nspeed ) , next),prev ))  ;
				}
			}
		}
		if(f)cout<<"unreachable"<<endl;
	}
	return 0;
}

