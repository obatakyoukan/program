#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
//MSC Minumum Set Cover 正しそうだが遅そう => 今日プロでは使いにくい
//if |s| = 2の過程はあまり早くならなかった.
//Maximum Matching 
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

struct MSC{
    ll n,m;
    vector< set<ll> > S;
    MSC() {}
    MSC(ll n):n(n){
	m = 0;
    }
    void add_cover( set<ll> &s){
	S.push_back( s );
	m++;
    }
    void add_cover( vector<ll> &s){
	set<ll> tmp;
	for(auto i:s)tmp.insert( i );
	add_cover( tmp );
    }
    //残りの要素でS[a]に含まれている要素を返す.
    set<ll>  SubCover( vector<ll> &rest , ll a ){
	set<ll> res;
	for(auto i:rest){
	    if( S[a].find( i ) != S[a].end() ) res.insert( i );
	}
	return res;
    }
    ll SubCoverDegree( vector<ll> &rest, ll a ){
	return SubCover( rest , a ).size();
    }

    //del 仕様に難あり?
    vector<ll> delete_element( vector<ll> &rest , ll a ){
	vector<ll> res;
	for(auto i:rest){
	    if( S[a].find( i ) == S[a].end() ) res.push_back( i );
	}
	return res;
    }
    ll calc( ){
	vector<ll> U(n);
	vector<ll> R(m);
	iota( U.begin() , U.end() , 0 );
	iota( R.begin() , R.end() , 0 );
	return calc( U , R );
    }
    ll calc( vector<ll> &U, vector<ll> &R ){
	if( U.size() == 0 || R.size() == 0 ) return 0;
	// 2. if S,R exsist such that S<= R 
	set<ll> except;
	for( auto i: R ){
	    set<ll> sub = SubCover( U , i );
	    if( sub.size() == 0 ) {
		except.insert( i );
		continue;
	    }
	    for( auto j:R){
		if( i == j ) continue;
		bool flag = true;
		// not find is exist
		// flag: true -> false
		for( auto k:sub )if( S[j].find( k ) == S[j].end() ) flag = false;
		if( flag ){//all S[i] elements  exist in S[j]
		    // if S[i] == S[j] -> 片方残すべき
		    if( sub.size() == SubCoverDegree( U , j ) &&  i < j )continue;
		    except.insert( i );
		    break;
		}
	    }
	}
	if( !except.empty() ){
	    vector<ll> nextR;
	    for(auto i:R)if( except.find( i ) == except.end() ) nextR.push_back( i );
	    return calc( U , nextR );
	}
	// 3. if u in U exsist such that there is unique s in R with u 
	set<ll> unique;
	for(auto i:U ){
	    vector<ll> having;
	    for(auto j:R){
		//have u
		if( S[j].find( i ) != S[j].end() ) having.push_back( j );
	    }
	    if( having.size() == 0 ){
		cerr<<"Maybe err: "<<i<<endl;
		for( auto j: U ){
		    cout<<j<<' ';
		}
		cout<<endl;
		for( auto j:R ){
		    cout<<"cover:"<<j<<endl;
		    for( auto k : SubCover( U, j ) ) cout<<k<<' ';
		    cout<<endl;
		}
		//cout<<endl;

		return inf;
	    }
	    if( having.size() == 1 ){
		for(auto j:having ) unique.insert( j );
	    }
	}
	if( !unique.empty() ){
	    vector<ll> nextU,nextR;
	    nextU = U;
	    for(auto i:unique ) nextU = delete_element( nextU , i );
	    for(auto i:R) if( unique.find( i ) == unique.end() ) nextR.push_back( i );
	    return unique.size() + calc( nextU , nextR );
	}

	// 4. choose a set s in R of maximum cardinality
	ll mc = -1;
	ll index = -1;
	for( auto i: R){
	    ll d = SubCoverDegree( U , i );
	    if( d > mc ){
		mc = d;
		index = i;
	    }
	}
	// 5. if |s| == 2
	if( mc == 2 ){
	    return Polynomial_MSC( U , R );
	}
	
	// 6. else
	vector<ll> nextU,nextR;
	nextU = delete_element( U , index );
	for( auto i:R )if( i != index ) nextR.push_back( i );
	return min( calc( U , nextR ) , 1 + calc( nextU , nextR ) );
    }
    //all s in R such that |s| = 2
    ll Polynomial_MSC(vector<ll> &U , vector<ll> &R){
	ll nn = 0;
	//U の残りをnnまで対応付けする.
	map<ll,ll> change;
	for( auto i:U ){
	    change[i] = nn;
	    nn++;
	}
	Match match( nn );
	for(auto i:R ){
	    set<ll> sub = SubCover( U , i );
	    vector<ll> subrest;
	    for( auto j:sub ) subrest.push_back( j );
	    if( subrest.size() !=2 ){
		cerr<<"Possible Danger"<<endl;
		cerr<<subrest.size()<<endl;
		continue;
	    }
	    match.add_edge( change[ subrest[0] ] , change[ subrest[1] ]);
	}
	ll d = match.MaximumMatch();
	return d + (nn - 2*d ); // Matching + Matching で選ばれなかった点
    }

};



int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int main(){

    ll r,c;
    cin>>r>>c;
    vector< vector<ll> > t(r+2,vector<ll>(c+2,-1) );
    ll cnt = 0;
    for(ll i=1;i<=r;i++){
	for(ll j=1;j<=c;j++){
	    char tmp;
	    cin>>tmp;
	    if(tmp=='.'){
		t[i][j] = cnt;
		cnt++;
	    }
	}
    }
    ll m = cnt;// vertex -> cover
    vector< set<ll> > g(m);
    set<mp> edge;//edge -> elements
    for(ll i=1;i<=r;i++){
	for(ll j=1;j<=c;j++){
	    if(t[i][j]==-1)continue;
	  //  g[t[i][j]].insert( t[i][j] );
	    for(ll k=0;k<4;k++){
		if( t[ i + dx[k] ][ j + dy[k] ] != -1 ){
		    ll mini = min( t[i][j] , t[ i + dx[k] ][ j + dy[k] ] );
		    ll maxi = max( t[i][j] , t[ i + dx[k] ][ j + dy[k] ] );
		    edge.insert( mp( mini , maxi ) );
		    //g[mini].insert( maxi );
		    //g[maxi].insert( mini );
		}
	    }
	}
    }
    cnt = 0;
    //cout<<edge.size()<<' '<<m<<endl;
    for( auto i:edge ){
	//cout<<i.first<<' '<<i.second<<endl;
	g[i.first].insert(cnt);
	g[i.second].insert(cnt);
	cnt++;
    }
    /*
    for( ll i=0;i<m;i++){
	cout<<i<<endl;
	for(auto j:g[i])cout<<j<<' ';
	cout<<endl;
    }*/

    MSC msc( edge.size() );
    for(ll i=0;i<m;i++){
	msc.add_cover( g[i] );
    }
    cout<<m-msc.calc()<<endl;// Minimum Dominating Set => U-M ( U:全体集合 , M:最小点被覆)
    return 0;
}

