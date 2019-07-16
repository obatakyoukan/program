#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int n;
    cin>>n;
    vector<int> p(n);
    for(int i=0;i<n;i++)cin>>p[i];
    vector<vector< bool> > dp(n+1,vector<bool>(n*100+1,false) );
    dp[0][0] = true;
    for(int i=0;i<n;i++){
	for(int j=0;j<n*100+1 ;j++){
	    if( dp[i][j] )dp[i+1][j] = true;
	    if( j>= p[i] && dp[i][ j-p[i] ] ) dp[i+1][j] = true;
	}
    }
    int cnt = 0;
    for(int i=0;i<n*100+1;i++)if(dp[n][i])cnt++;
    cout<<cnt<<endl;
    return 0;
}

