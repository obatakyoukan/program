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
    set<ll> Neighbor(vector<ll> &rest , ll v){
	set<ll> res;
	for(auto i:rest)if(mat[i][v])res.insert( i );
	return res;
    }
    set<ll> Neighbor2(vector<ll> &rest, ll v){
	set<ll> res;
	set<ll> Neighborhood = Neighbor( rest , v );
	Neighborhood.insert( v );
	for( auto i: Neighborhood ){
	    set<ll> add = Neighbor( rest , i );
	    //for(auto j:add) if( Neighborhood.find( j ) == Neighborhood.end() ) res.insert( j );
	    for(auto j:add) if( j!= v ) res.insert( j );//どっちが正しい?????????????????????????
	}
	return res;
    }
    set<ll> Mirrors( vector<ll> &rest , ll v ){// if u in N^2(v) and N(v)/N(u) is clique , u is clique
	set<ll> res;
	set<ll> NV = Neighbor( rest, v );
	set<ll> N2 = Neighbor2( rest , v );
	for(auto u: N2 ){
	    set<ll> NU = Neighbor( rest , u );
	    vector<ll> next;
	    for(auto i:NV)if( NU.find( i ) == NU.end() ) next.push_back( i );
	    if( Is_Clique( next ) )res.insert( u );
	}
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
	// Case: minimum degree is 0 or 1
	if( mind <= 1 ){
	    vector<ll> next;
	    res += st0.size() + st1.size();
	    set<ll> del1;//degree 1 の隣接点を削除する
	    ll cnt = 0;//degree 1 で辺が繋がったものを数える
	    for(auto i:st1){
		del1.insert(i);
		for(auto j:rest )
		    if(mat[i][j] )
			if( st1.find( j ) != st1.end() ) cnt++;//片方削除できない
			else del1.insert(j);
	    }
	    res -= cnt/2;
	    for(auto i:rest){
		if( st0.find( i ) ==st0.end() && del1.find( i ) == del1.end()  ) next.push_back( i );
	    }
	    return res + MIS( next );
	}
	// Case: minimum degree is 2
	if( mind == 2 ){
	    vector<ll> subedge = SubEdge( rest , mini );
	    ll u0 = subedge[0];
	    ll u1 = subedge[1];
	    set<ll> del;
	    del.insert( u0 );
	    del.insert( u1 );
	    del.insert( mini );
	    if( mat[u0][u1] ){
		vector<ll> next;
		for( auto i:rest ) if( del.find( i ) == del.end() ) next.push_back( i );
		return 1 + MIS( next );
	    }else{
		set<ll> N1 = Neighbor( rest  , mini );//N[v]
		N1.insert( mini );
		set<ll> N2 = Neighbor2( rest , mini );//N^2(v)
		if( N2.size() == 1 ){//There is some miss in this range
		    ll w = *N2.begin();
		    set<ll> NW = Neighbor( rest , w );//N[w]
		    NW.insert( w );
		    vector<ll> next1,next2;//1:w and mini(v) 2: two Neighbors of v
		    for(auto i:rest){
			if( N1.find( i ) == N1.end() && N2.find( i ) == N2.end() ){//N^2[v] not find
			    next2.push_back( i );
			    if( NW.find( i ) == NW.end() ) next1.push_back( i );
			}
		    }
		    return max( 2 + MIS( next1 ) , 2 + MIS( next2 ) );
		}else{
		    vector<ll> next1,next2;//
		    set<ll> MV = Mirrors( rest , mini );
		    MV.insert( mini );
		    for( auto i:rest ){
			if( N1.find( i ) == N1.end() ) next1.push_back( i );
			if( MV.find( i ) == MV.end() ) next2.push_back( i );
		    }
		    return max( 1 + MIS( next1 ) , MIS( next2 ) );
		} 
	    }
	}
	// Case: minimum degree is 3
	if( mind == 3 ){
	    vector<ll> sub = SubEdge( rest , mini );
	    vector<ll> subd = SubDegree( sub );
	    vector<ll> next1,next2;//next1:  G\N[v]
	    set<ll> N1 = Neighbor( rest , mini );
	    N1.insert( mini );
	    set<ll> MV = Mirrors( rest , mini );// M[v]
	    for(auto i:rest ){
		if( N1.find( i ) == N1.end() )next1.push_back( i );
	    }
	    
	    ll edge_cnt = 0;//number of edge 
	    for(auto i:subd) edge_cnt += i;

	    if( edge_cnt == 0 ){
		if( !MV.empty() ){
		    for(auto i:rest){
			if( MV.find( i ) == MV.end() && i != mini ){//next2 : G\( M(v) or {v} )
			    next2.push_back( i );
			}
		    }
		    return max( 1 + MIS( next1 ) , MIS(next2 ) );
		}else{
		    vector<ll> nextt[3];
		    //next1: G/(N[ {u1,u2} ]  ) , next2: G/(N[ {u1,u3} ] or {u2} ) , next3: G/(N[ {u2,u3} ] or {u1} )
		    set<ll> NN[3];
		    for( int i=0;i<3;i++ ) NN[i] = Neighbor(rest , sub[i] );
		    for( int i=0;i<3;i++ ) NN[i].insert( sub[i] );
		    
		    for( int i=0;i<3;i++ ){
			for(auto j:rest ){
			    if( (i==0|| j != sub[i] )&& NN[(i+1)%3].find( j ) == NN[(i+1)%3].end() && NN[(i+2)%3].find( j ) == NN[(i+2)%3].end() ) nextt[i].push_back( j );
			    //if( sub[i] != j &&  NN[(i+1)%3].find( j ) == NN[(i+1)%3].end() && NN[(i+2)%3].find( j ) == NN[(i+2)%3].end() ) nextt[i].push_back( j );
			    //下の方ができれば早そうだけど嘘だと思う. あとで確かめ
			}
		    }
		    return max( max( 1 + MIS( next1 ) , 2 + MIS( nextt[0] ) ),  max(2+ MIS( nextt[1] ) , 2 + MIS( nextt[2] ) ) );
		}
	    }else if( edge_cnt == 1 || edge_cnt == 2 ){
		for(auto i:rest){
		    if( MV.find( i ) == MV.end() && i != mini ){//next2 : G\( M(v) or {v} )
			next2.push_back( i );
		    }
		}
		return max( 1 +  MIS( next1 ) , MIS( next2 ) );
	    }else{
		return 1 + MIS( next1 );
	    }
	}
	// Case: Maximum Degree is more and equals 6
	if( maxd >= 6 ){
	    vector<ll> next1,next2;//next1: G/N[v] , next2: G/{v} . v is maximum degree.
	    set<ll> NM = Neighbor( rest , maxi );
	    NM.insert( maxi );
	    for(auto i:rest){
		if( NM.find( i ) == NM.end() ){
		    next1.push_back( i );
		}
		if( i != maxi ){
		    next2.push_back( i );
		}
	    }
	    return max( 1 + MIS( next1 ) , MIS( next2 ) );
	}
	// Case: Disconnect Graph
	vector<ll> sub = Connect( rest );
	if( sub.size() != rest.size() ){
	    vector<ll> subrest;
	    for(auto i:rest){
		if( *lower_bound( sub.begin() , sub.end() , i ) != i ){
		    subrest.push_back( i );
		}
	    }
	    return MIS(sub) + MIS(subrest);
	}
	// Case: G is 4 or 5 regular 
	if( maxd == mind &&  ( mind == 4 || mind == 5 ) ){
	    ll v = rest[0];
	    set<ll> NV = Neighbor( rest , v );
	    NV.insert( v );
	    set<ll> MV = Mirrors( rest , v );
	    MV.insert( v );
	    vector<ll> next1,next2;
	    for(auto i:rest){
		if( NV.find( i ) == NV.end() ){
		    next1.push_back( i );
		}
		if( MV.find( i ) == MV.end() ){
		    next2.push_back( i );
		}
	    }
	    return max( 1 + MIS( next1 ) , MIS( next2 ) );
	}
	// Case: Maximum degree is 5 and Minimum degree is 4
	if( maxd == 5 && mind == 4 ){
	    ll v=-1,w=-1;// d(v) == 5 , d(w) == 4 (v,w)in edge 
	    for( auto i:rest){
		if( v != -1 )break;
		if( SubDegree( rest , i ) != 5 )continue;
		for( auto j:rest){
		    if( mat[i][j] &&SubDegree( rest , j ) == 4 ){
			v = i;
			w = j;
			break;
		    }
		}
	    }
	    vector<ll> next1,next2,next3;
	    set<ll> NV = Neighbor( rest , v );
	    set<ll> NW = Neighbor( rest , w );
	    NV.insert( v );
	    NW.insert( w );
	    set<ll> MV = Mirrors( rest, v );
	    MV.insert( v );
	    for(auto i:rest){
		if( NV.find( i ) == NV.end() ){
		    next1.push_back( i );
		}
		if( MV.find( i ) == MV.end() ){//M(v) or {v}
		    if( NW.find( i ) == NW.end() ){
			next2.push_back( i );
		    }
		    if( i != w ){
			next3.push_back( i );
		    }
		}
	    }
	    return max( max( 1 + MIS( next1 ) , 1 + MIS( next2 ) ) , MIS( next3 ) );
	}

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

