#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf = 1e9;
typedef pair<ll,mp> mmp;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

vector<ll> bfs(vector<vector<bool> > used,vector<mp> go,int s){
	int n = go.size();
    	vector<ll> res(n,inf);
	int h = used.size();
	int w = used[0].size();
	vector<vector<ll> > cost(h,vector<ll>(w,inf) );
	queue<mmp> q;
	q.push( mmp(0,mp(go[s].first,go[s].second ) ) );
	while(!q.empty() ){
	    mmp now = q.front();
	    q.pop();
	    ll c = now.first;
	    //cout<<c<<endl;
	    ll x = now.second.first;
	    ll y = now.second.second;
	    if(!used[x][y] )continue;
	    used[x][y] = false;
	    cost[x][y] = min(cost[x][y],c);
	    for(int i=0;i<4;i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!used[nx][ny] ) continue;
		q.push( mmp( c + 1,mp(nx,ny) ) );
	    }
	}
	for(int i=0;i<n;i++) res[i] = min(res[i], cost[ go[i].first ][ go[i].second ] );
	return res;
}

int main(){
    while(1){
	int w,h;
	cin>>w>>h;
	if(w==0)break;
	vector<vector<bool> > used(h+2,vector<bool>(w+2,false) );
	int s;
	vector<mp> go;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			char tmp ;
			cin>>tmp;
			if(tmp=='o'){
				s = go.size();
				go.push_back(mp(i,j) );
				used[i][j] = true;
			}else if(tmp=='*'){
				go.push_back(mp(i,j) );
				used[i][j] = true;
			}else if(tmp=='.'){
				used[i][j] = true;
			}
		}
	}
	swap(go[0],go[s]);//
	s = 0;
	int n = go.size();
	if(n >11){
		cout<<"error"<<endl;
		return 1;
	}	
	vector<vector<ll> > g(n);
	for(int i=0;i<n;i++) g[i] = bfs ( used, go ,i);
	//cout<< "OK"<<endl;
	/*for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<g[i][j]<<' ';
		}
		cout<<endl;
	}*/
	vector<vector<ll> > dp( (1<<n),vector<ll>(n,inf) ); // [bit][i] bit 1のとき未訪問, 0 のとき訪問済み i は最後に来た場所
	dp[(1<<n)-1][0] = 0;
	for(int i= (1<<n)-1;i>=0;i--){//TSP
		for(int j = 0;j<n;j++)
		    for(int k=0;k<n;k++)
			if( !( (i>>k) & 1 ) )dp[i][j] = min(dp[i][j] , dp[ i | (1<<k) ][k] + g[j][k] ) ;  
	}
	ll m  = inf ;
	for(int i=0;i<n;i++){
		m = min( m, dp[1<<i][i] );
	}
	//for(int i=0;i<n;i++)for(int j=0;j<n;j++) m = min( m , res[ (1<<n)-1][i][j] );
	if( m == inf){
		cout<<-1<<endl;
	}else{
		cout<<m<<endl;
	}
    }
	return 0;
}

