#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    set<ll> s;
    ll a[] = { 1, 1,2,3,4,5,6,1,2,3};
    for(ll i=0;i< 10;i++){
	if( s.insert( a[i] ).second )cout<<i<<' '<<a[i]<<endl;
    }
    return 0;
}

