#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
template< typename T , typename OT =  T >
struct SegmentTree{
    using F = function< T (T,T)  >;
    using G = function< T(T,OT,int) >;
    using H = function< OT(OT,OT) >;

    int size;
    vector< T > data;
    vector< OT > lazy;

    const F f;
    const G g;
    const H h;
    const T M1;
    const OT OM;


    SegmentTree(int n,const F f,const G g, const H h,const T &M1, const OT OM ): f(f),g(g),h(h),M1(M1),OM(OM){
	size = 1;
	while(size < n) size <<= 1;
	data.assign(2*size,M1);
	lazy.assign(2*size,OM);
    }

    void set(int k, const T &x){
	data[k+ size] = x;
    }
    void build(){
	for(int k = size-1;k>0;k--){
	    data[k] = f( data[2*k] , data[2*k+1] );
	}
    }
    void propagate(int k,int len){
	if(lazy[k] != OM){
	    if( k < size ){
		lazy[2*k] = h( lazy[2*k] , lazy[k] );
		lazy[2*k+1] = h( lazy[2*k+1] , lazy[k] );
	    }
	    data[k] = g(data[k] , lazy[k], len);
	    lazy[k] = OM;
	}
    }
    T update(int a,int b,const OT &x, int k,int l,int r ){
	propagate(k,r-l);
	if( r <= a || b<= l){
	    return data[k];
	}else if(a<=l && r<=b){
	    lazy[k] = h(lazy[k] ,x);
	    propagate(k,r-l);
	    return data[k];
	}else{
	    return data[k] = f( update(a,b,x,2*k,l,(l+r)>>1 ) , update(a,b,x,2*k+1,(l+r)>>1,r)  );
	}
    }

    T update(int a,int b,const OT &x){
	return update(a,b,x,1,0,size);
    }

    T query(int a,int b,int k , int l , int r){
	propagate(k,r-l);
	if( r <= a || b<= l){
	    return M1;
	}else if(a<=l && r<=b){
	    return data[k];
	}else{
	    return f( query(a,b,2*k,l,(l+r)>>1 ) , query(a,b,2*k+1,(l+r)>>1,r)  );
	}
    }

    T query(int a,int b){
	return query(a,b,1,0,size);
    }
    T operator[] (const int &k){
	return query(k,k+1);
    }


};




int main(){

    return 0;
}

