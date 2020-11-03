#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf = 1e12;


int main(){
    while(1){
	int n,m;
	cin>>n>>m;
	if(n==0)break;
	//ll gs[n][n]={inf},gl[n][n]={inf};
	vector<vector<ll> > gs(n,vector<ll>(n,inf) ),gl;
	gl = gs;
	ll x[m],y[m],t[m];
	char state[m];
	for(int i=0;i<n;i++) gs[i][i] = gl[i][i] = 0;
	for(int i=0;i<m;i++){
	    cin>>x[i]>>y[i]>>t[i]>>state[i];
	    x[i]--,y[i]--;
	    if(state[i]=='S'){
		gs[x[i]][y[i]] = min(gs[x[i]][y[i]],t[i]);
		gs[y[i]][x[i]] = min(gs[y[i]][x[i]],t[i]);
	    }else{
		gl[x[i]][y[i]] = min(gl[x[i]][y[i]],t[i]);
		gl[y[i]][x[i]] = min(gl[y[i]][x[i]],t[i]);
	    }
	}

	for(int k=0;k<n;k++){
	    for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
		    gs[i][j] = min(gs[i][j],gs[i][k] + gs[k][j]);
		    gl[i][j] = min(gl[i][j],gl[i][k] + gl[k][j]);
		}
	    }
	}
	int r;
	cin>>r;
	ll z[r];
	for(int i=0;i<r;i++) cin>>z[i],z[i]--;
	//ll dp[r][n] = { inf };
	vector<vector<ll> > dp(r,vector<ll>(n,inf) );
	dp[0][z[0]] = 0;
	for(int i=0;i<r-1;i++){
	    for(int j=0;j< n;j++){
		dp[i+1][j] = min(dp[i+1][j],dp[i][j] + gl[ z[i] ][ z[i+1] ] );
		for(int k=0;k<n;k++){
		    dp[i+1][j] = min(dp[i+1][j],dp[i][k] + gl[z[i]][k] + gs[k][j] + gl[j][z[i+1]] ); 
		}
	    }
	}
	/*for(int i=0;i<r;i++){
	    for(int j = 0;j<n;j++) cout<<dp[i][j]<<' ';
	    cout<<endl;
	}*/

	ll res = inf;
	for(int i=0;i<n;i++) res = min(res,dp[r-1][i] );
	cout<<res<<endl;
    }

    return 0;
}

