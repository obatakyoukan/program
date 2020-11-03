#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,int> mp;
typedef pair<mp,int> mmp;
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
		vector<vector<bool> > used(n,vector<bool>(31,false) );
		priority_queue<mmp,vector<mmp>,greater<mmp> > q;
		q.push(mmp(mp(0.0,1),s) );
		bool f = true;
		while(!q.empty() ){
			mmp now = q.top();
			q.pop();
			double cost = now.first.first;
			int speed = now.first.second;
			int nn = now.second;
			if( nn==gg && speed==0){
				cout<<cost<<endl;
				f = false;
				break;
			}
			if(speed == 0) continue;
			if(used[nn][speed])continue;
			used[nn][speed] = true;
			for(int i=0;i<g[nn].size();i++){
			    	double d = g[nn][i].first.first;
				int  c = g[nn][i].first.second; 
				int next = g[nn][i].second;
				for(int j=-1;j<2;j++){
				    	int nspeed  = speed + j;
					if( speed > c || speed <=0) continue;
					if(used[next][nspeed])continue;
					q.push(mmp(mp(cost + d/speed,nspeed),next) );
				}
			}
		}
		if(f)cout<<"unreachable"<<endl;
	}
	return 0;
}

