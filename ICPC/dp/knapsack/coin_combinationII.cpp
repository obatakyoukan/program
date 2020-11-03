#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    ll n,k,l,r;
    cin>>n>>k>>l>>r;
    vector<ll> a(n),b,c;
    for(ll i=0;i<n;i++)cin>>a[i];
    for(ll i=0;i<n/2;i++) b.push_back(a[i]);
    for(ll i=n/2;i<n;i++) c.push_back(a[i]);

    ll bn = n/2,cn = n-n/2;
    vector<mp> bb,cc;//i個の数字でできる数
    for(ll i=0;i< (1<<bn);i++){
	ll cnt = 0;
	ll sum = 0;
	for(ll j=0;j<bn;j++){
	    if( (i>>j)&1 ){
		cnt++;
		sum += b[j];
	    }
	}
	bb.push_back( mp(cnt, sum ) );
    }
    for(ll i=0;i< (1<<cn);i++){
	ll cnt = 0;
	ll sum = 0;
	for(ll j=0;j<cn;j++){
	    if( (i>>j)&1 ){
		cnt++;
		sum += c[j];
	    }
	}
	cc.push_back( mp(cnt, sum) );
    }
    sort( bb.begin(), bb.end() );
    sort( cc.begin(), cc.end() );
    ll res = 0;
    for(auto it:bb){
	ll bi = it.first;
	ll bs = it.second;
	auto s = lower_bound(cc.begin(),cc.end(), mp(k-bi,l-bs) );
	auto t = upper_bound(cc.begin(),cc.end(), mp(k-bi,r-bs) );
	res += (t-s);
    }
    cout<<res<<endl;
    return 0;
}

