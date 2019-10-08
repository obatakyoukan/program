#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    hash<bitset<512> > hash_fn;
    for(ll i=0;i<100;i++){
	bitset<512> bit(i);
	cout<<i<<' '<<hash_fn(bit)<<endl;
    }

    return 0;
}

