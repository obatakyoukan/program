#include<bits/stdc++.h>
using namespace std;
#define INF 0
typedef long long int ll;

typedef struct ST{ 
	vector<ll> a;
	int n;
	void init(vector<ll> &b){
		int size= b.size();
		n=1;
		while(n<size) n*=2;
		a =vector<ll> (2*n-1,INF);
		for(int i=0;i<size;i++)	a[i+n-1] = b[i];
		for(int i=n-2;i>=0;i--) a[i] = max(a[i*2+1],a[i*2+2]); //RMQ
	}
	void update(int k,ll val){
		k+=n-1;
		a[k] = val;
		while(k>0){
			k = (k-1)/2;
			a[k] = max(a[k*2+1],a[k*2+2]);//RMQ
		}
	}
	// [aa,b)の最大値
	// kは節点番号l,rはその節点が[l,r)に対応
	// get(aa,b,0,0,n)
	ll get(int aa,int b,int k,int l,int r){
		//[aa,b)に完全に[l,r)が含んでいる場合 この節点
		if(aa<=l && r<=b) return a[k];
		
		//[aa,b)と[l,r)が交差しなければ INF
		if(r<=aa || b<=l) return INF;
		ll vl = get(aa,b,k*2+1,l,(l+r)/2);
		ll vr = get(aa,b,k*2+2,(l+r)/2,r);
		return max(vl,vr);
	}
	ll find(int aa,int b){
		return get(aa,b,0,0,n);
	}	
}ST;



int main(){
	int n;
	cin>>n;
	vector<ll> b(n+2,0);
	ST seg;
	seg.init(b);
	vector<ll> a(n),h(n);
	for(int i=0;i<n;i++) cin>>h[i];
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++){
	    ll M  = seg.find(0,h[i]);
	    seg.update(h[i], M + a[i] ) ;
	}
	cout<<seg.find(0,n+1)<<endl;

	return 0;
}
