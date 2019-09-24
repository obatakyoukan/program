#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

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
	// 6. else
	vector<ll> nextU,nextR;
	nextU = delete_element( U , index );
	for( auto i:R )if( i != index ) nextR.push_back( i );
	return min( calc( U , nextR ) , 1 + calc( nextU , nextR ) );
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
    cout<<m-msc.calc()<<endl;
    return 0;
}

