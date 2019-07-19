#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int n,k;
    cin>>n>>k;
    vector<int> h(n,inf);
    for(int i=0;i<n;i++)cin>>h[i];
    vector<int> dp(n,inf);
    dp[0] = 0;
    //dp[1] = abs( h[1]-h[0] );
    for(int i=1;i<n;i++){
	for(int j=0;j<k && i-j-1>=0;j++)dp[i] = min( dp[i-j-1] + abs(h[i]-h[i-j-1]) , dp[i]) ;
    }
    cout<<dp[n-1]<<endl;
    return 0;

}

