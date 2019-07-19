#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int n;
    cin>>n;
    vector<int> h(n,inf);
    for(int i=0;i<n;i++)cin>>h[i];
    vector<int> dp(n,inf);
    dp[0] = 0;
    dp[1] = abs( h[1]-h[0] );
    for(int i=2;i<n;i++){
	dp[i] = min( dp[i-1] + abs(h[i]-h[i-1]) , dp[i-2] + abs(h[i] -h[i-2] ) );
    }
    cout<<dp[n-1]<<endl;
    return 0;

}

