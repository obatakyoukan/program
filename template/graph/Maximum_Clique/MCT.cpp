#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
typedef pair<ll,mp> mmp;
ll inf =  1e9;
#define Th1 0.4
#define Th2 0.1

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
    pair< vector<ll> , map< ll , ll  > > Intersection( vector<ll> &R , map< ll , ll > &No , ll p ){
	vector<ll> newR ;
	map< ll , ll > newNo;
	for( auto i:R ){
	    if( i!=p && g[p].find( i ) != g[p].end() ) newR.push_back( i ) , newNo[i] = No[i];
	}
	return pair< vector<ll> , map< ll , ll >  >( newR ,newNo );
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
    ll No_MAX(vector<ll> &R , map< ll , ll > &No){
	ll res = 0;
	for(auto i:R)res = max( res , No[i] );
	return res;
    }
    vector<ll> extend_sort(vector<ll> &R , map< ll , ll > &No){// Noも一緒に動かす?
	if( R.size() == 0 ) return R;
	vector<mmp> A( R.size() );
	vector<ll> deg( R.size() , 0 );
	for(ll i=0;i<R.size();i++) deg[i] = SubDegree( R , R[i] );
	for(ll i=0;i<R.size();i++) A[i] = mmp( deg[ i ] , mp( -No[ R[i] ], R[i]  ) );
	sort( A.begin() , A.end() );
	reverse( A.begin() , A.end() );
	vector<ll> res( R.size() );
	for(ll i=0;i<R.size();i++) res[i] = A[i].second.second;
	return res;
    }
    void init_Color(vector<ll> &R,map< ll , ll  > &No){
	for(ll i=0;i<R.size();i++){
		set<ll> cnt;
		for(ll j=0;j<i;j++){
		    if( mat[ R[i] ][ R[j] ] && No[ R[j] ]!=0 ){
			cnt.insert( No[ R[j] ] );
		    }
		}
		for(ll k=1;k<=cnt.size()+2;k++)if( cnt.find( k ) == cnt.end() ){
		    No[ R[i] ] = k;
		    break;
		}
	}
    }
    void RE_NUMBER( ll p ,ll Noth, ll Nop ,vector< set<ll> > &C , ll mode = 0 ){//mode0 k2: k1+1 to Noth , mode1 k2: 1 to Noth
	for( ll k1 = 1 ; k1 <=  Noth - 1 ; k1++ ){
	    set<ll> SEKI = Intersection( C[k1] , p );
	    ll k2 = k1 + 1 ;
	    if( mode == 1 ) k2 = 1;
	    ll q = *SEKI.begin();
	    for( ; k2 <= Noth ; k2++ ){
		if( Intersection( C[k2] , p ).empty() ){
		    C[ Nop ].erase( p );
		    C[ k1 ].erase( q );
		    C[ k1 ].insert( p );
		    C[ k2 ].insert( q );
		   // No[ p ] = k1;
		   // No[ q ] = k2;
		}
	    }
	}
    }
    map< ll , ll >  NUMBER_R(vector<ll> &R ,map< ll , ll > &No,set<ll> &Q ,ll mode = 0){//mode0: NUMBER_R , NUMBER_R+
	ll No_M = No_MAX( R , No );
	ll Noth = Q_MAX.size()-Q.size();
	if( No_M <= Noth ) return No;
	vector< set< ll > > C( No_M + 1 );
	for( auto i:R ){
	    C[ No[i] ].insert( i );
	}
	if( mode == 0 ){
	    for( auto i:R  ){
	    	if( No_M == i ){
			RE_NUMBER( i ,Noth, No[i] , C ); 
	    	}
	    }
	}else{
	    for(ll i=No_M;i>Noth;i--){
		for(auto p:C[i]){
		   RE_NUMBER( p, Noth , No[p] , C , mode );
		}
	    }
	}
	map< ll , ll > resNo;
	for(ll i=0;i<R.size();i++){
	    for(ll k = 0;k<No_M;k++){
		if( C[k].find( R[i] ) != C[k].end() ){
		    resNo[ R[i] ] = k;
		    break;
		}
	    }
	}
	return resNo;
    }
    

    /*
    vector<ll> NUMBER_RL(vector<ll> &R, vector<ll> &No){

    }*/

    bool Add_Clique( set<ll> &Q , ll p ){
	for( auto i:Q )if( !mat[i][p] ) return false;
	return true;
    }
    void UpdateClique( set<ll> &Q ){
	if( Q.size() > Q_MAX.size() ){
	 //   cout<<Q.size()<<endl;
	    Q_MAX = Q;
	}
    }
    ll CNTV( map< ll , ll > &No , ll Noth ){
	ll cnt = 0;
	for( auto i: No )if( i.second > Noth ) cnt++;
	return cnt;
    }
    double Dens( vector<ll> &R ){
	double cnt1 = 0;
	double cnt2 = R.size() * ( R.size() -1 );
	for( auto i:R )
	    for( auto j:R )
		if( mat[i][j] && i!=j )cnt1++;
	return cnt1/cnt2;
    }

    void Maximum_Clique(){
	vector<ll> R(n);
	set<ll> Q;
	map< ll , ll > No;
	iota( R.begin() , R.end() , 0 );
	init_Color(R, No);
	R = extend_sort( R , No );
	Q_MAX = Q;
	return Maximum_Clique( R , Q , No );
    }
    void Maximum_Clique(vector<ll> &R , set<ll> &Q , map< ll ,ll > &No , ll stage = 1){
	if( Q.size() + R.size() <= Q_MAX.size() ) return;
	while( !R.empty() ){
	    ll p = R.back();
	    if( !Add_Clique( Q , p ) ) continue;
	    if(  (stage==1 && Q.size() + No_MAX( R , No ) > Q_MAX.size() )||( stage!=1 && Q.size() + No[p] > Q_MAX.size() ) ){
		Q.insert( p );
		UpdateClique( Q );
		auto it = Intersection( R , No, p );
		vector<ll> newR = it.first;
		map<ll,ll> newNo = it.second;
		if( newR.empty() ){
		    Q.erase( p );
		    R.pop_back();
		    continue;
		}
		ll newstage;
		double dens = Dens( newR );
		double T =  ( (double) CNTV( newNo , Q_MAX.size() - Q.size() ) )/ newR.size() * dens;
		if( stage == 1 && Th1 <= T ){
		    extend_sort( newR , newNo );
		    NUMBER_R( newR , newNo , Q , 1 );
		    newstage = 1;
		}else{
		    NUMBER_R( newR , newNo , Q );
		    newstage = 2;
		}
		//init_Color( newR , newNo );
		Maximum_Clique( newR , Q , No , newstage );
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

