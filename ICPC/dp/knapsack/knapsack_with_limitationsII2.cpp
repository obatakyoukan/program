#include<bits/stdc++.h>//c++14
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e15;
ll x = 30;
ll N,W;
vector<ll> dp,v,w,m;
ll solve(){//O(NWlogm) 
    vector<ll> dp(N*x*50+1,inf);//x*x? x*50(x*v_i) できればx*xの方が安心???
    dp[0] = 0;
    for(ll i=0;i<N;i++){//前半, 各ナップサックのx個で価値iを作る重さ最小dp[i]を探す.
	ll num = min(m[i],x) ;
	m[i] -= num;
	for(ll j=1;num > 0; j<<=1 ){
	    ll mul = min(j,num);//最後を上手くやる
	    if(!j)break;
	    for(ll k=N*x*50; k>=0;k--){
		if(k+mul*v[i]<=N*x*50)dp[k+mul*v[i]] = min(dp[k+ mul*v[i] ],dp[k] + mul*w[i]);
	    }
	    num-=mul;
	}
    }
    vector<ll> ord(N);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](ll a,ll b){ return v[a]*w[b] > v[b]*w[a]; } );// (v/w)の降順
    //for(int i=0;i<ord.size();i++)cout<<ord[i]<<' '<<(double)v[ ord[i] ]/w[ ord[i] ] <<endl;
    ll ans = 0;
    for(ll i=0;i<=N*x*50;i++){//後半, 残りを上手くやる?
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

