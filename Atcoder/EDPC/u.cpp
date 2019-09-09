#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e15;
ll mod = 1e9+7;
ll n;
vector<ll> dp;
vector<vector<ll> > a;
ll solve(ll s){
    if( dp[s] != -inf ) return dp[s];
    ll res = 0;
    for(ll i=0;i<n;i++)for(ll j=i+1;j<n;j++)if( ( (s>>i)&1) && ( (s>>j)&1) )res += a[i][j];
    for(ll t = (s-1)&s; t > 0 ; t = ( (t-1)&s )){
	res = max(res, solve(t) + solve(s^t) );
    }
    return dp[s] = res;
}

int main(){
    cin>>n;
    dp = vector<ll>( (1<<n) , -inf );
    a = vector<vector<ll> > ( n ,vector<ll> (n,0) );
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>a[i][j];
    cout<<solve( (1<<n)-1 ) <<endl;
    return 0;
}

