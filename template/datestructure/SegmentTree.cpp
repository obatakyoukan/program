#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
template< typename T >
struct SegmentTree{
    using F = function< T (T,T)  >;

    int size;
    vector< T > seg;

    const F f;
    const T M1;

    SegmentTree(int n,const F f,const T &M1): f(f),M1(M1){
	size = 1;
	while(size < n) size <<= 1;
	seg.assign(2*size,M1);
    }

    void set(int k, const T &x){
	seg[k+ size] = x;
    }
    void build(){
	for(int k = size-1;k>0;k--){
	    seg[k] = f( seg[2*k] , seg[2*k+1] );
	}
    }
    void update(int k,const T &x){
	k += size;
	seg[k] = x;
	while( k>>=1 ){
	    seg[k] = f(seg[2*k] , seg[2*k+1] );
	}
    }
    T query(int a,int b){
	T L = M1, R = M1;
	for( a += size, b += size; a < b ;  a >>= 1 , b >>= 1 ){
	    if( a & 1 ) L = f(L , seg[a++]);
	    if( b & 1 ) R = f(seg[--b], R) ;
	}
	return f(L,R);
    }
    T operator[](const int &k){
	return seg[ k+size ];
    }
};




int main(){
    // aoj DSL 2A
    int n,q;
    cin>>n>>q;
    SegmentTree<ll> seg( n , [](ll a,ll b){ return min(a,b) ;} , (1LL<<31)-1);
    for(int i=0;i<q;i++){
	ll t,a,b;
	cin>>t>>a>>b;
	if(t==0){
	    seg.update(a,b);
	}else{
	    cout<<seg.query(a,b+1)<<endl;
	}
    }
    return 0;
}

