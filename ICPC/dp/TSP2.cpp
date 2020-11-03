#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
#define inf 1e9
int main(){
    int v;
    cin>>v;
    vector<vector<int> > g(v,vector<int>(v,inf) );
    int e;
    cin>>e;
    for(int i=0;i<e;i++){
	int s,t,d;
	cin>>s>>t>>d;
	g[s][t] = d;
    }
    vector<vector<int> > dp( 1<<v , vector<int>(v,inf) );
    dp[ (1<<v) -1 ][0] = 0;
    for( int i = (1<<v) -1 ; i >=  0 ; i-- ){
	for( int j = 0 ; j < v ; j++ ){ // from
	    for( int k = 0 ; k < v ; k++ ){ // to
		if( ( (i>>k) & 1 ) == 0 ){
		    dp[i][j] = min(dp[i][j] , dp[ i | (1<<k) ] [k] + g[k][j] );
		}
	    }
	}
    }
    if( dp[0][0] == inf ){
	cout<<-1<<endl;
    }else{
	cout<<dp[0][0]<<endl;
    }
    return 0;
}

