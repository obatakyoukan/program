#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
vector< mp > dp;
vector< ll > a;
mp calc( ll i ){
    if( i == -1 ){
	return mp(0,-1);
    }
    return mp( a[i] , i );
}
mp calc( mp a , mp b ){
    set< mp > st;
    st.insert( calc( a.first ) );
    st.insert( calc( a.second ) );
    st.insert( calc( b.first ) );
    st.insert( calc( b.second ) );
    auto it = st.end();
    ll i,j;
    it--;
    i = it->second;
    it--;
    j = it->second;
    return mp(i,j);
}


int main(){
    ll n;
    cin>>n;
    a = vector<ll>( 1<<n , 0 );
    for(ll i=0;i<(1<<n);i++) cin>> a[i];
    dp = vector< mp >( 1<<n );// or で上から2つ
    for(ll i=0;i<(1<<n);i++) dp[ i ] = mp( i , -1 );
    for(ll i=1;i<(1<<n);i++){
	for(ll j=0;j<n;j++){
	    dp[i] = calc( dp[i] , dp[ i & ~(1<<j) ] ); 
	}
    }
    ll res = 0;
    for(ll i=1;i<(1<<n);i++){
	res = max(res, a[ dp[i].first ] + a[ dp[i].second ] );
	cout<<res<<endl;
    }
    return 0;
}

