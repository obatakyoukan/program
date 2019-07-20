#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9 + 7;

int main(){
    ll h,w;
    cin>>h>>w;
    vector<vector<bool> > used(h,vector<bool>(w,false) );
    for(int i=0;i<h;i++){
	for(int j=0;j<w;j++){
	    char tmp ;
	    cin>>tmp;
	    if(tmp == '.'){
		used[i][j] = true;
	    }
	}
    }

    vector<vector<ll>  > dp(h,vector<ll>(w,0) );
    for(int i=0;i<w;i++)if(used[0][i])dp[0][i] = 1;
    else break;
    for(int i=0;i<h;i++)if(used[i][0])dp[i][0] = 1;
    else break;

    for(int i=1;i<h;i++)
	for(int j=1;j<w;j++){
	    if(used[i][j]) dp[i][j] = ( dp[i][j-1] + dp[i-1][j] )%mod;
	}
    cout<<dp[h-1][w-1]<<endl;
    return 0;
}

