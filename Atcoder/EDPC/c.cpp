#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int n;
    cin>>n;
    vector<vector<int> > ac(n,vector<int>(3,0) );
    for(int i=0;i<n;i++){
	cin>>ac[i][0]>>ac[i][1]>>ac[i][2];
    }
    int ans = 0;
    vector<vector<int> > dp(n+1,vector<int>(3,0) );
    for(int i=1;i<=n;i++){
	for(int j=0;j<3;j++){
	    for(int k=1;k<=2;k++){
		dp[i][j] = max(dp[i][j], dp[i-1][(j+k)%3] + ac[i-1][j] );
		ans = max(ans,dp[i][j]);
	    }
	}
    }
    cout<<ans<<endl;
    return 0;
}

