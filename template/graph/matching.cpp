#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;



struct Match{
#define EVEN(x) ( mu[x] == x || ( mu[x] != x && phi[mu[x]]!= mu[x] ) )
#define ODD(x) ( mu[x] != x && phi[ mu[x] ] == mu[x] && phi[x] != x  )
#define OUTER(x) ( mu[x] !=x && phi[ mu[x] ] == mu[x] && phi[x] == x )
    ll n;
    vector<vector<ll> > g;
    Match(){}
    Match( ll n ):n(n){
	g = vector<vector<ll> >(n);
    }
    void add_edge(ll a,ll b){
	g[a].push_back(b);
	g[b].push_back(a);
    }

    //マッチングの枝を返す.
    vector< mp > calc(){
	vector< mp > res;
	//Initilize
	vector<ll> mu(n),phi(n),rho(n),scanned(n);
	iota( mu.begin() , mu.end() , 0 );
	iota( phi.begin() , phi.end() , 0 );
	iota( rho.begin() , rho.end() , 0 );
	ll x = -1;
	while(1){
	    if( x < 0 ){ //select even
		for( x = 0 ; x < n && ( scanned[x] || !EVEN(x) ) ; x++ );
		if( x == n )break; 
	    }
	    ll y = -1; // select incident
	    for( auto e:g[x] ) if( OUTER( e ) || ( EVEN(e) && rho[e] != rho[x] ) ) y = e;
	    if( y == -1 ) scanned[x] = true , x = -1;
	    else if( OUTER( y ) ) phi[y] = x;//growth
	    else{
		vector<ll> dx(n,-2),dy(n,-2); //!TRICK! x%2 -->  x>=0
		for(ll k=0,w=x; dx[w] < 0 ; w = k%2 ? mu[w]:phi[w]) dx[w] = k++;
		for(ll k=0,w=y; dy[w] < 0 ; w = k%2 ? mu[w]:phi[w]) dy[w] = k++;
		bool vertex_disjoint = true;
		for(ll v=0;v<n;v++)if( dx[v]>=0 && dy[v]>0 ) vertex_disjoint = false;
		if( vertex_disjoint ){//argument
		    for(ll v=0;v<n;v++)if( dx[v]%2 ) mu[ phi[v] ] = v , mu[v] = phi[v] ;
		    for(ll v=0;v<n;v++)if( dy[v]%2 ) mu[ phi[v] ] = v , mu[v] = phi[v] ;
		    mu[x] = y , mu[y] = x , x = -1;
		    for(ll v=0;v<n;v++) phi[v] = rho[v] = v ,scanned[v] = false;
		}else{ //shirink
		    ll r = x,d = n;
		    for(ll v=0;v<n;v++)if( dx[v] >= 0 && dy[v] >= 0 && rho[v] == v && d > dx[v] ) d = dx[v] , r = v;
		    for(ll v=0;v<n;v++)if( dx[v] <= d && dx[v]%2 && rho[ phi[v] ] != r ) phi[ phi[v] ] = v;
		    for(ll v=0;v<n;v++)if( dy[v] <= d && dy[v]%2 && rho[ phi[v] ] != r ) phi[ phi[v] ] = v;
		    if( rho[x] != r ) phi[x] = y;
		    if( rho[y] != r ) phi[y] = x;
		    for(ll v=0;v<n;v++)if( dx[ rho[v] ] >= 0 || dy[ rho[v] ] >= 0 ) rho[v] = r;
		}
	    }
	}
	for(ll u = 0; u < n ; u++) if( u < mu[u] ) res.push_back( mp( u,mu[u] ) );
	return res;
    }

    ll MaximumMatch(){
	return calc().size() ;
    }

};


int main(){
    ll n;
    cin>>n;
    vector< mp > point(2*n);
    Match match(2*n);
    for(ll i=0;i<2*n;i++){
	ll a,b;
	cin>>a>>b;
	point[i] = mp(a,b);
    }
    for(ll i=0;i<n;i++){
	for(ll j=n;j<2*n;j++){
	    if( point[i].first < point[j].first && point[i].second < point[j].second ){
		match.add_edge( i , j );
	    }
	}
    }
    cout<<match.MaximumMatch()<<endl;
    return 0;
}

