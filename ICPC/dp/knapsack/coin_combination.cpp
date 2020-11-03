#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    ll n,v;
    cin>>n>>v;
    vector<ll> a(n),b(n),c(n),d(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    for(int i=0;i<n;i++) cin>>c[i];
    for(int i=0;i<n;i++) cin>>d[i];
    vector<ll> ab,cd;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)ab.push_back( a[i] + b[j] );
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cd.push_back( c[i] + d[j] );
    sort(ab.begin(),ab.end());
    sort(cd.begin(),cd.end());
    ll res = 0;
    for(int i=0;i<n*n;i++){
	auto s = lower_bound(cd.begin(),cd.end(),v-ab[i]);
	auto t = upper_bound(cd.begin(),cd.end(),v-ab[i]);
	res += (t-s);
    }
    cout<<res<<endl;
    return 0;
}

