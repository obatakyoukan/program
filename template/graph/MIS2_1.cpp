#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

//行列形式(mat)
//Max Independent Set(MIS)
//Maximum Clique
// Add application Disconnect Graph => かなり早い
//https://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/me
// MIS1_1 => MIS1_2 844ms => 6ms


struct Graph{
    ll n;
    vector<vector<bool> > mat;
    vector<ll> d;

    //初期化(Initialize)
    Graph(){}
    Graph(ll n):n(n){
	mat = vector<vector<bool> >(n,vector<bool>(n,false) );
	d = vector<ll>(n,0);
    }
    Graph(vector<vector<bool> > &mat):mat(mat),n(mat.size() ){
	d = vector<ll>(n,0);
	for(ll i=0;i<n;i++)
	    for(ll j=0;j<n;j++)
		if( mat[i][j] ) d[i]++;
    }

    //Add Edge: 辺の追加
    void add_edge(ll a,ll b){
	mat[a][b] = mat[b][a] = true;
	d[a]++;
	d[b]++;
    }
    //Complement Graph(補グラフ)
    //自己ループなし?
    Graph Complement(){
	vector<vector<bool> > res(n,vector<bool>(n,false) );
	for(ll i=0;i<n;i++)
	    for(ll j=0;j<n;j++){
		if(i==j)continue;
		res[i][j] = !mat[i][j];
	    }
	return Graph(res);
    }
    //Maximum Clique 最大クリーク
    //
    ll Maximum_Clique(){
	return Complement().MIS();
    }
    bool Is_Clique( vector<ll> &rest ){
	for(auto i:rest){
	    for(auto j:rest){
		if( i!=j && !mat[i][j] ) return false;
	    }
	}
	return true;
    }

    vector<ll> SubEdge( vector<ll> &rest , ll a){//Neibor ?
	vector<ll> res;
	for(auto i:rest)if(mat[a][i])res.push_back(i);
	return res;
    }
    vector<ll> SubDegree( vector<ll> &rest ){
	vector<ll> res( rest.size() , 0 );
	for(int i=0;i<rest.size();i++){
	    for(int j=0;j<rest.size();j++){
		if( mat[ rest[i] ][ rest[j] ] ) res[i]++;
	    }
	}
	return res;
    }
    ll SubDegree(vector<ll> &rest, ll a){
	ll res = 0;
	for(auto i:rest){
	    if(mat[a][i])res++;
	}
	return res;
    }

    //隣接点( 自分を含まない )
    set<ll> Neighbor(vector<ll> &rest , ll v , ll mode = 0 ){
	set<ll> res;
	for(auto i:rest)if(mat[i][v])res.insert( i );
	if( mode != 0 ) res.insert( v ); // N[v]
	return res;
    }
    set<ll> Neighbor2(vector<ll> &rest, ll v , ll mode = 0){
	set<ll> res;
	set<ll> Neighborhood = Neighbor( rest , v );
	Neighborhood.insert( v );
	for( auto i: Neighborhood ){
	    set<ll> add = Neighbor( rest , i );
	    //for(auto j:add) if( Neighborhood.find( j ) == Neighborhood.end() ) res.insert( j );
	    for(auto j:add) if( j!= v ) res.insert( j );//どっちが正しい?????????????????????????
	}
	if( mode != 0 ){
	    for( auto i:Neighborhood ) res.insert( i );// N2[v]
	}
	return res;
    }
    set<ll> Mirrors( vector<ll> &rest , ll v , ll mode = 0 ){// if u in N^2(v) and N(v)/N(u) is clique , u is clique
	set<ll> res;
	set<ll> NV = Neighbor( rest, v );
	set<ll> N2 = Neighbor2( rest , v );
	for(auto u: N2 ){
	    set<ll> NU = Neighbor( rest , u );
	    vector<ll> next;
	    for(auto i:NV)if( NU.find( i ) == NU.end() ) next.push_back( i );
	    if( Is_Clique( next ) )res.insert( u );
	}
	if( mode != 0 ) res.insert( v );//M[v]
	return res;
    }
    // rest[0]から連結している部分を取り出す　size != rest.size() のとき, dis connect
    //
    vector<ll> Connect(vector<ll> &rest){
	vector<ll> res;
	res.push_back(rest[0]);
	vector<bool> used(rest.size() , true);
	used[0] = false;
	queue<ll> q;
	q.push( rest[0]  );

	while( !q.empty() ){
	    ll i = q.front();
	    q.pop();
	    for(auto j:rest){
		if( mat[ i ][j] ){
		    auto it = lower_bound( rest.begin() , rest.end() , j );
		    int index = it- rest.begin() ;
		    if( !used[ index ] ) continue;
		    used[ index ] = false;
		    q.push( j );
		    res.push_back( j );
		}
	    }
	}

	sort(res.begin(),res.end() );
	return res;
    }
    // Case:
    pair<ll , vector<ll> > Case1(vector<ll> &rest, set<ll> &st0 ,set<ll> &st1 ){
	ll res = 0;
	vector<ll> next;
	res += st0.size() + st1.size();
	set<ll> del1;
	ll cnt = 0;
	for( auto i:st1 ){
	    del1.insert( i );
	    for( auto j:rest ){
		if( mat[i][j] ){
		    if( st1.find( j ) == st1.end() ) del1.insert( j );
		    else cnt++;
		}
	    }
	}
	res -= cnt/2;
	for(auto i:rest)if( st0.find( i ) == st0.end() && del1.find( i ) == del1.end() ) next.push_back( i );
	return pair<ll, vector<ll> > ( res , next );
    }

    vector<ll>  Case_connect( vector<ll> &rest , vector<ll> &sub ){
	vector<ll> subrest;
	for(auto i:rest ){
	    if( *lower_bound( sub.begin() , sub.end() , i ) != i ){
		subrest.push_back( i );
	    }
	}
	return subrest;
    }
    vector<ll>  Case_select( vector<ll> &rest , ll v){
	set<ll> Neighborhood = Neighbor( rest , v ,1);//N[v]
	vector<ll> next;
	for(ll i:rest)if( Neighborhood.find( i ) == Neighborhood.end() ) next.push_back( i );
	return next;
    }
    vector<ll> Case_discard( vector<ll> & rest , set<ll> v){
	vector<ll> next;
	for(auto i:rest ){
	    if( v.find( i ) == v.end() ) next.push_back( i );
	}
	return next;
    }
    vector<ll> Case_discard( vector<ll> &rest, ll v ){
	vector<ll> next;
	for(auto i:rest)if( i!=v)next.push_back( i );
	return next;
    }
    set<ll> UnionSet( set<ll> &a,set<ll> &b ){
	set<ll> res;
	for(auto i:a ) res.insert( i );
	for(auto i:b ) res.insert( i );
	return res;
    }
    //
    vector< pair<ll , vector<ll> >  > Case2_2_1(vector<ll> &rest, set<ll> N1, ll w ){
	set<ll> NW = Neighbor( rest , w , 1 );
	vector< pair<ll,vector<ll> > > res(2);
	vector<ll> next1,next2;// next1: v, w select , next2: neibors of v select
	for(auto i:rest){
	    if( N1.find( i ) == N1.end() && i!=w ){
		next2.push_back( i );
		if( NW.find( i ) == NW.end() ) next1.push_back( i );
	    }
	}
	res[0] = pair<ll,vector<ll> >( 2 , next1 );
	res[1] = pair<ll,vector<ll> >( 2 , next2 );
	return res;
    }
    vector< pair<ll, vector<ll> > > Case6( vector<ll> &rest ){
	vector< pair<ll,vector<ll> > > res(3);
	ll v = -1,w = -1;
	for(auto i:rest){
	    if( v != -1 )break;
	    if( SubDegree( rest , i ) != 5 ) continue;
	    for(auto j:rest){
		if( mat[i][j] && SubDegree(rest , j) == 4 ){
		    v = i;
		    w = j;
		}
	    }
	}
	vector<ll> next1 = Case_select( rest , v );
	set<ll> MV = Mirrors( rest , v , 1 );
	vector<ll> nrest = Case_discard( nrest , MV );
	vector<ll> next2 = Case_select( nrest , w );
	vector<ll> next3 = Case_discard( nrest , w );
	res[0] = pair<ll,vector<ll> > (1 , next1 );
	res[1] = pair<ll,vector<ll> > (1 , next2 );
	res[2] = pair<ll,vector<ll> > (0 , next3 );
	return res;
    }
    ll MIS(){
	vector<ll> rest(n);
	iota( rest.begin() , rest.end() , 0 );
	return MIS(rest);
    }

    ll MIS(vector<ll> &rest){
	ll res = 0;
	if(rest.size() == 0) return 0;
	ll mind = 2*n,mini = n-1;// mind = minimum degree mini = minimum index
	ll maxd = -1 , maxi = n-1;// maxd = maximum degree maxi = maximum index

	set<ll> st0,st1;
	for(auto i:rest){
	    ll di = SubDegree(rest,i);
	    if( mind > di ){//最小次数
		mind = di;
		mini = i;
	    }
	    if( maxd < di ){//最大次数
		maxd = di;
		maxi = i;
	    }
	    if(di == 0){
		st0.insert( i );
	    }
	    if(di == 1){
		st1.insert( i );
	    }
	}
	// Case1: minimum degree is 0 or 1
	if( mind <= 1 ){
	    pair<ll , vector<ll> > res = Case1( rest , st0 ,st1 );
	    return res.first + MIS( res.second );
	}
	// Case Connect: Disconnect Graph 入れる位置は重要かも!!!
	vector<ll> sub = Connect( rest );
	if( sub.size() != rest.size() ){
	    vector<ll> subrest = Case_connect( rest , sub );
	    return MIS(sub) + MIS(subrest);
	}
	
	// Case2: minimum degree is 2
	if( mind == 2 ){
	    vector<ll> subedge = SubEdge( rest , mini );
	    ll u0 = subedge[0];
	    ll u1 = subedge[1];
	    if( mat[u0][u1] ){//Case2_1: V select
		vector<ll>  res = Case_select( rest , mini );
		return 1 + MIS( res );
	    }else{//Case2_2
		set<ll> N1 = Neighbor( rest  , mini );//N[v]
		N1.insert( mini );
		set<ll> N2 = Neighbor2( rest , mini );//N^2(v)
		if( N2.size() == 1 ){//Case2_2_1
		    ll w = *N2.begin();
		    vector< pair<ll, vector<ll> > > res = Case2_2_1( rest , N1 , w );
		    return max( res[0].first + MIS( res[0].second ) , res[1].first + MIS( res[1].second ) );
		}else{//Case2_2_2
		    set<ll> MV = Mirrors( rest , mini ,1);
		    vector<ll> next1 = Case_select( rest , mini ) , next2 = Case_discard( rest , MV );
		    return max( 1 + MIS( next1 ) , MIS( next2 ) );
		} 
	    }
	}
	// Case3: minimum degree is 3
	if( mind == 3 ){
	    vector<ll> sub = SubEdge( rest , mini );
	    vector<ll> subd = SubDegree( sub );
	    vector<ll> next1,next2;//next1:  G\N[v]
	    set<ll> N1 = Neighbor( rest , mini , 1 );
	    set<ll> MV = Mirrors( rest , mini , 1 );// M[v]
	    next1 = Case_select( rest , mini );
	    ll edge_cnt = 0;//number of edge 
	    for(auto i:subd) edge_cnt += i;

	    if( edge_cnt == 0 ){
		if( !MV.empty() ){
		    MV.insert( mini );
		    next2 = Case_discard( rest , MV );
		    return max( 1 + MIS( next1 ) , MIS(next2 ) );
		}else{
		    vector<ll> nextt[3];
		    //next1: G/(N[ {u1,u2} ]  ) , next2: G/(N[ {u1,u3} ] or {u2} ) , next3: G/(N[ {u2,u3} ] or {u1} )
		    set<ll> NN[3];
		    for( int i=0;i<3;i++ ) NN[i] = Neighbor(rest , sub[i] );
		    for( int i=0;i<3;i++ ) NN[i].insert( sub[i] );
		    for( int i=0;i<3;i++){
			set<ll> Union = UnionSet( NN[(i+1)%3] , NN[(i+2)%3] );
			if( i != 0 ) Union.insert( sub[i] );
			nextt[i] = Case_discard( rest , Union );
		    }	    
		    return max( max( 1 + MIS( next1 ) , 2 + MIS( nextt[0] ) ),  max(2+ MIS( nextt[1] ) , 2 + MIS( nextt[2] ) ) );
		}
	    }else if( edge_cnt == 1 || edge_cnt == 2 ){
		next2 = Case_discard( rest , MV );
		return max( 1 +  MIS( next1 ) , MIS( next2 ) );
	    }else{
		return 1 + MIS( next1 );
	    }
	}
	// Case4: Maximum Degree is more and equals 6
	if( maxd >= 6 ){
	    vector<ll> next1,next2;//next1: G/N[v] , next2: G/{v} . v is maximum degree.
	    next1 = Case_select( rest , maxi );
	    next2 = Case_discard( rest , maxi );
	    return max( 1 + MIS( next1 ) , MIS( next2 ) );
	}
	// Case5: G is 4 or 5 regular 
	if( maxd == mind &&  ( mind == 4 || mind == 5 ) ){
	    ll v = rest[0];
	    set<ll> MV = Mirrors( rest , v , 1 );
	    vector<ll> next1 = Case_select( rest , v ),next2 = Case_discard( rest , MV );
	    return max( 1 + MIS( next1 ) , MIS( next2 ) );
	}
	// Case6: Maximum degree is 5 and Minimum degree is 4
	if( maxd == 5 && mind == 4 ){
	    auto res = Case6( rest );
	    return max( max( res[0].first + MIS( res[0].second ) , res[1].first + MIS( res[1].second ) ) , res[2].first + MIS( res[2].second ) );
	}
	/*
	// Case: minimum degree is else ここまでに終了する
	//cout<<"ERROR"<<endl;
	vector<ll> nei;
	nei.push_back( mini );
	for(auto i:rest ){
	    if( mat[mini][i] ) nei.push_back(i);
	}
	for(auto i:nei){//iを取り除く
	    set<ll> st;//delete point 
	    st.insert(i);
	    for(auto j:rest){
		if(mat[i][j])st.insert(j);
	    }
	    vector<ll> next;
	    for(auto j:rest ){
		if(st.find( j ) == st.end() ) next.push_back(j);
	    }
	    //削除する隣接点の次数を下げるときかく( Oを落としたいとき )
	    res = max(res,MIS(next) );
	    //削除する隣接点の次数を戻すときかく
	}
	*/
	return 1+res;
    }

};


int main(){
    ll n,m;
    cin>>n>>m;
    Graph g(n);
    for(ll i=0;i<m;i++){
	ll a,b;
	cin>>a>>b;
	a--,b--;
	g.add_edge(a,b);
    }
    cout<<g.MIS()<<endl;
    return 0;
}

