#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
typedef pair<ll,mp> mmp;
ll inf =  1e9;

struct Graph{
    ll n;
    set<ll>  Q_MAX;// Maximum Clique
    vector<vector<bool> > mat;//隣接行列
    vector< set<ll> > g;//隣接set
    vector<bool> used;
    vector<ll> degree;
    Graph(){}
    Graph( ll n ):n(n){
	g = vector< set<ll> > (n);
	degree = vector<ll> (n,0);
	used = vector<bool>(n , false);
	mat = vector<vector<bool> >( n ,vector<bool>(n,false) );
    }
    void add_edge(ll a,ll b){
	mat[a][b] = true;
	mat[b][a] = true;
	degree[a]++;
	degree[b]++;
	g[a].insert( b );
	g[b].insert( a );
    }
    struct StepCount{
	ll i1,i2;
	StepCount():i1(0),i2(0) {}
    };
    vector<ll> Intersection( vector<ll> &R, ll p ){
	vector<ll> res;
	for(auto i:R){
	    if( i!=p && g[p].find( i ) != g[p].end() ) res.push_back( i );
	}
	return res;
    }
    pair< vector<ll> , vector<ll> > Intersection( vector<ll> &R , vector<ll> &No , ll p ){
	vector<ll> newR , newNo;
	for( auto i:R ){
	    if( i!=p && g[p].find( i ) != g[p].end() ) newR.push_back( i ) , newNo.push_back( i );
	}
	return pair< vector<ll> , vector<ll> >( newR ,newNo );
    }
    set<ll> Intersection( set<ll> &R , ll p ){
	set<ll> res;
	for( auto i:R ){//i!=p ????
	    if( g[p].find( i ) != g[p].end() && i != p) res.insert( i );
	}
	return res;
    }
    ll SubDegree(vector<ll> &R , ll p){
	ll cnt = 0;
	for(auto i:R )if( mat[i][p] ) cnt++;
	return cnt;
    }
    ll No_MAX(vector<ll> &R , vector<ll> &No){
	ll res = 0;
	for(auto i:R)res = max( res , No[i] );
	return res;
    }
    vector<ll> extend_sort(vector<ll> &R , vector<ll> &No){// Noも一緒に動かす?
	if( R.size() == 0 ) return R;
	vector<mmp> A( R.size() );
	vector<ll> deg( R.size() , 0 );
	for(ll i=0;i<R.size();i++) deg[i] = SubDegree( R , R[i] );
	for(ll i=0;i<R.size();i++) A[i] = mmp( deg[ R[i] ] , mp( -No[ R[i] ], R[i]  ) );
	sort( A.begin() , A.end() );
	reverse( A.begin() , A.end() );
	vector<ll> res( R.size() );
	for(ll i=0;i<R.size();i++) res[i] = A[i].second.second;
	return res;
    }
    void init_Color(vector<ll> &R,vector<ll> &No){
	for(ll i=0;i<R.size();i++){
		set<ll> cnt;
		for(ll j=0;j<i;j++){
		    if( mat[ R[i] ][ R[j] ] && No[ j ]!=-1 ){
			cnt.insert( No[ j ] );
		    }
		}
		for(ll k=1;k<=cnt.size()+2;k++)if( cnt.find( k ) == cnt.end() ){
		    No[ i ] = k;
		    break;
		}
	}
    }
    bool Add_Clique( set<ll> &Q , ll p ){
	for( auto i:Q )if( !mat[i][p] ) return false;
	return true;
    }
    void UpdateClique( set<ll> &Q ){
	if( Q.size() > Q_MAX.size() ){
	    cout<<Q.size()<<endl;
	    Q_MAX = Q;
	}
    }
    void Maximum_Clique(){
	vector<ll> R(n);
	set<ll> Q;
	vector<ll> No(n);
	iota( R.begin() , R.end() , 0 );
	init_Color(R, No);
	R = extend_sort( R , No );
	Q_MAX = Q;
	return Maximum_Clique( R , Q , No );
    }
    void Maximum_Clique(vector<ll> &R , set<ll> &Q , vector<ll> &No){
	if( Q.size() + R.size() <= Q_MAX.size() ) return;
	while( !R.empty() ){
	    ll p = R.back();
	    if( Add_Clique(Q,p) && Q.size() + No_MAX( R , No ) > Q_MAX.size() ){
		Q.insert( p );
		UpdateClique( Q );
		auto it = Intersection( R , No, p );
		vector<ll> newR = it.first;
		vector<ll> newNo = it.second;
		if( R.empty() ) continue;
		extend_sort( newR , newNo );
		init_Color( newR , newNo );
		Maximum_Clique( newR , Q , No );
	    }
	    Q.erase( p );
	    R.pop_back();
	}
    }

};

int main(){
    ll n,m;
    cin>>n>>m;
    Graph G(n);
    for(ll i=0;i<m;i++){
	ll a,b;
	cin>>a>>b;
	a--,b--;
	G.add_edge( a, b );
    }
    G.Maximum_Clique();
    cout<<G.Q_MAX.size()<<endl;
    return 0;
}

