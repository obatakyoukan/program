#include<bits/stdc++.h>//c++14
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e15;
ll x = 32;
ll N,W;
vector<ll> dp,v,w,m;
ll solve(){//O(NWlogm) 
    vector<ll> dp(N*x*x+1,inf);
    dp[0] = 0;
    for(ll i=0;i<N;i++){
	ll num = min(m[i],x) ;
	m[i] -= num;
	for(ll j=1;num > 0; j<<=1 ){
	    ll mul = min(j,num);//最後を上手くやる
	    if(!j)break;
	    for(ll k=N*x*x; k>=0;k--){
		if(k+mul*v[i]<=N*x*x)dp[k+mul*v[i]] = min(dp[k+ mul*v[i] ],dp[k] + mul*w[i]);
	    }
	    num-=mul;
	}
    }
    vector<ll> ord(N);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](ll a,ll b){ return v[a]*w[b] > v[b]*w[a]; } );
    ll ans = 0;
    for(ll i=0;i<=N*x*x;i++){
	ll lim = W-dp[i];
	if(lim < 0 ) continue;
	ll res = i;
	for(ll j=0;j<N;j++){
	    ll k = ord[j];
	    ll c = min( m[k],lim/w[k] );
	    lim -= w[k]*c;
	    res += v[k]*c;
	}
	ans = max(ans,res);
    }
    return ans;
}

int main(){
    cin>>N>>W;
    v = vector<ll>(N);
    w = vector<ll>(N);
    m = vector<ll>(N);
    for(int i=0;i<N;i++)cin>>v[i]>>w[i]>>m[i];
    cout<<solve()<<endl;
    return 0;
}

