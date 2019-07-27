#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
ll mod = 1e9 + 7;
struct matrix{
    int h,w;
    vector<vector<ll> > mat;
    matrix(){}
    matrix(int h,int w,ll val):h(h),w(w),mat(h,vector<ll>(w,val) ){}
    matrix(int h,int w):h(h),w(w),mat(h,vector<ll>(w) ){}
    matrix(int n):h(n),w(n),mat(n,vector<ll>(n,0) ){}
    matrix(vector<vector<ll> > mat):h(mat.size() ),w(mat[0].size() ),mat(mat){}
    //単位行列
    void eye(){
	if(h!=w)return ;
	for(int i=0;i<h;i++)for(int j=0;j<w;j++)if(i==j)mat[i][j] = 1;
	else mat[i][j] = 0;
    }
    //演算子
    matrix operator + (matrix a){
	vector<vector<ll> > res(h,vector<ll>(w,0) );
	for(int i=0;i<h;i++)
	    for(int j=0;j<w;j++){
		res[i][j] = (mat[i][j] + a.mat[i][j])%mod;
	    }
	return matrix(res);
    }
    matrix operator - (matrix a){
	vector<vector<ll> > res(h,vector<ll>(w,0) );
	for(int i=0;i<h;i++)
	    for(int j=0;j<w;j++){
		res[i][j] = (mat[i][j] - a.mat[i][j])%mod;
	    }
	return matrix(res);
    }
    matrix operator * (matrix a){
	vector<vector<ll> > res(h,vector<ll>(a.w,0)  );
	for(int i=0;i<h;i++)
	    for(int j=0;j<a.w;j++)
		for(int k=0;k<w;k++) {
		    res[i][j] += mat[i][k]*a.mat[k][j];
		    res[i][j] %= mod;
		}
	return matrix(res);
    }

    ll sum(){
	ll res = 0;
	for(int i=0;i<h;i++)for(int j=0;j<w;j++) {
	    res += mat[i][j];
	    res %= mod;
	}
	return res;
    }
};



int main(){
    ll n,k;
    cin>>n>>k;
    vector<matrix> dp( 62 , matrix(n) );
    vector<vector<ll> > a(n,vector<ll>(n,0) );
    for(int i=0;i<n;i++)for(int j=0;j<n;j++) cin>>a[i][j];
    dp[0] = a;
    for(int i=1;i<62;i++){
	dp[i] = dp[i-1] * dp[i-1];
    }
    matrix res = matrix(n);
    res.eye();
    for(int i=0;i<62;i++){
	if( (k>>i)&1 ) res = res * dp[i];
    }
    cout<<res.sum()<<endl;
    return 0;
}

