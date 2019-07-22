#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9 + 7;

int main(){
    int n;
    cin>>n;
    vector<vector<ll> > a(n,vector<ll>(n,0) );
    vector<ll> dp( 1<<n ,0 ) ;
    dp[0] = 1;
    for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)cin>>a[i][j];

    for(int i=1;i<(1<<n);i++){//ビットが立っている女性が0~(j-1)番目までの男性とマッチングしている個数 
	int j = __builtin_popcount(i);
	for(int k = 0;k<n;k++){//(j-1)番目の男性とk番目の女性がマッチする
	    if( ((i>>k)&1) == 1 &&  a[j-1][k] == 1 ) dp[i] += dp[ i^(1<<k)] ,dp[i]%=mod;
	}
    }
    cout<< dp[ (1<<n)-1 ] << endl;
    return 0;
}

