#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e15;
vector<vector<ll> > dp;
vector<ll> a,sum;
ll solve(ll l,ll r){//[l,r)
    if(dp[l][r] != 0 ) return dp[l][r];
    if( l+1 == r ) return dp[l][r] = 0;
    ll res = inf;
    for(int i=l+1;i<r;i++) res = min( res , solve(l,i)+solve(i,r) );
    return dp[l][r] = res + sum[r] -sum[l];
}
int main(){
    int n;
    cin>>n;
    dp = vector<vector<ll> > (n+1,vector<ll>(n+1,0) );
    a=vector<ll>(n,0);
    for(int i=0;i<n;i++)cin>>a[i];
    sum = vector<ll>(n+1,0);
    for(int i=1;i<=n;i++)sum[i] = sum[i-1] + a[i-1];
    //for(int i=0;i<=n;i++)cout<<sum[i]<<endl;
    cout<<solve(0,n)<<endl;

    return 0;
}

