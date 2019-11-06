#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
#define Th1 0.4
#define Th2 0.1

struct Graph{
    int n,pk;
    vector<vector<bool> > mat;
    vector<set<int> > C;
    set<int> Q,QMAX;
    struct Vertex{
	int i,d,exd;
	Vertex(){}
	Vertex(int i,int d=0 ,int exd = 0):i(i),d(d),exd(exd){}
	void set_degree( vector<int> &R , vector<vector<bool> > &mat){
	    d = 0;
	    for(int j=0;j<R.size();j++ ){
		if( mat[i-1][ R[j] ] ) d++;
	    }
	}
	void set_exdegree( vector<int> &R , vector<vector<bool> >&mat){//全てのdegreeは求められている前提
	    exd = 0;
	    for(int j=0;j<R.size();j++){
		if( mat[i-1][ R[j] ] ) exd++;
	    }
	}
    };

    vector<Vertex> V;//動かさないつもり 基本参照とdegree color管理
    void set_degrees( vector<int> &R ){
	for(int i=0;i<R.size();i++) V[ R[i] ].set_degree( R , mat);
    }
    void set_exdegrees( vector<int> &R , bool update = false ){
	if( !update )set_degrees( R );
	for(int i=0;i<R.size();i++) V[ R[i] ].set_exdegree( R , mat);
    }

    //bool desc_degree(const int i,const int j){ return V[i].d > V[j].d ; }
    struct desc_degree{
	vector< Vertex > V;
	map<int , int > No;
	desc_degree(){}
	desc_degree( vector<  Vertex > &V ):V(V){}
	desc_degree( vector<  Vertex > &V , map<int,int> &No ):V(V),No(No){}
	bool operator()( const int i, const int j ){
	    return V[i].d !=  V[j].d ? V[i].d > V[j].d : No[i] < No[j];
	}
	void clear(){ V.clear() , No.clear(); }
    };
    void degree_sort( vector<int> &R ){
	set_degrees( R );
	desc_degree DESK( V );
	sort( R.begin() , R.end() , DESK );
	DESK.clear();//全部消えたらこれが怖い
    }
    void degree_sort( vector<int> &R , map<int,int> &No){
	set_degrees( R );
	desc_degree DESK( V , No );
	sort( R.begin() , R.end() , DESK );
	DESK.clear();//全部消えたらこれが怖い
    }

    struct leef_degree{
	vector< Vertex > V;
	map<int , int > No;
	leef_degree(){}
	leef_degree( vector<  Vertex > &V ):V(V){}
	leef_degree( vector<  Vertex > &V , map<int,int> &No ):V(V),No(No){}
	bool operator()( const int i, const int j ){
	    return No[i] !=  No[j] ? No[i] < No[j] : V[i].d > V[j].d;
	}
	void clear(){ V.clear() , No.clear(); }
    };
    void leef_sort( vector<int> &R ){
	set_degrees( R );
	leef_degree LF( V );
	sort( R.begin() , R.end() , LF );
	LF.clear();
    }
    void leef_sort( vector<int> &R , map<int,int> &No ){
	set_degrees( R );
	leef_degree LF( V , No);
	sort( R.begin() , R.end() , LF );
	LF.clear();
    }

    Graph( int n ):n(n){
	C = vector<set<int> >(n+1);
	mat = vector<vector<bool> >(n,vector<bool>(n,false) );
	V = vector< Vertex >( n );
	for(int i=0;i<n;i++) V[i] = Vertex( i + 1 );

    }
    Graph( vector<vector<bool> > &mat , int n ):n( n ),mat(mat){
	C = vector<set<int> >(n+1);
	V = vector< Vertex >( n );
	for(int i=0;i<n;i++) V[i] = Vertex( i + 1 );
    }

    void add_edge(int a, int b){
	mat[a][b] = mat[b][a] = true;
    }
    double dens( vector<int> &R ){
	int cnt = 0;
	for(int i=0;i<R.size();i++){
	    for(int j=0;j<R.size();j++){
		if( mat[ R[i] ][ R[j] ] )cnt++;
	    }
	}
	if( R.size() <= 1 ) return 1;
	return (double)cnt/( R.size()* (R.size() -1 ) );
    }

    bool cut1(int pi, set<int> &A){
	for(auto i:A)if( mat[ pi ][ i ] ) return true;
	return false;
    }
    vector<int> cut1_1(int pi , set<int> &A){
	vector<int> res;
	for(auto i:A)if( mat[ pi ][ i ] ) res.push_back( i );
	return res;
    }
    void cut2( vector<int> &A , vector<int> &B ){
	for(int i=0;i<A.size()-1;i++){
	    if( mat[ A[ A.size()-1] ][ A[i] ] ) B.push_back( A[i] );
	}
    }
    void cut2( vector<int> &A , vector<int> &B , map<int,int> &NoA , map<int,int > &NoB){
	for(int i=0;i<A.size()-1;i++){
	    if( mat[ A[ A.size()-1] ][ A[i] ] ) B.push_back( A[i] ), NoB[ A[i] ] = NoA[ A[i] ];
	}
    }
    map< int , int > init_color( vector<int> &R , vector<set<int> > &CC){
	map<int,int> No;
	//int max_degree = V[ R[0] ].d;
	for(auto i:R ){
	    int k = 1;
	    while( cut1( i , CC[k] ) )k++;
	    No[ i ] = k;
	    CC[k].insert( i );
	}
	leef_sort( R , No );
	return No;
    }

    void Re_NUMBER( int p , int Nop ,map<int,int> &No, vector< set<int> > &CC, bool one = false){
	int Noth = QMAX.size() - Q.size();
	for(int k1 = 1 ; k1 < Noth ; k1++ ){
	    vector<int> qq = cut1_1( p , CC[k1] );
	    if( qq.size() == 1 ){
		int q = qq[0];
		int k2 = k1+1;
		if( one ) k2 = 1;
		for( ; k2 <= Noth ; k2++){
		    if( !cut1( q , CC[ k2 ] ) ){
			CC[ Nop ].erase( p );
			CC[ k1 ].erase( q );
			CC[ k1 ].insert( p );
			CC[ k2 ].insert( q );
			//No[ p ] = k1;
			//No[ q ] = k2;
			return ;
		    }
		}
	    }
	}
    }
    void NUMBER_R( vector<int> &R , map<int,int> &No, vector<set<int> > &CC , bool plus = false){
	int Noth = QMAX.size() - Q.size() ;
	int MNO = 0;
	for(auto i:R) MNO = max( MNO , No[i] );
	for(int i=0;i<R.size();i++){
	    if( ( plus && No[ R[i] ] > Noth ) || ( !plus && No[ R[i] ] > Noth && No[ R[i] ] == MNO ) ){
		Re_NUMBER( R[i] , No[R[i] ], No , CC , plus );
	    }
	}
	//leef_sort( R );
    }
    void NUMBER_RL( vector<int> &R , map<int,int> &No , map<int,int> &newNo , vector<set<int> > &CC){
	for(int i=1;i<=R.size();i++){
	    CC[i].clear();
	}
	int Noth = QMAX.size() - Q.size();
	int maxno = 1;
	for(int i=0;i<R.size();i++){
	    if( No[ R[i] ] <= Noth ){
		int k = No[ R[i] ];
		if( k > maxno ) maxno = k;
		CC[k].insert( R[i] );
		newNo[ R[i] ] = k;
	    }
	}
	for(int i=0;i<R.size();i++){
	    if( No[ R[i] ] > Noth ){
		int p = R[i];
		int k = 1;
		while( cut1( p , CC[k] ) ) k++;
		if( k > maxno ) maxno = k;
		CC[k].insert( p );
		newNo[ p ] = k;
		if( k > Noth ) Re_NUMBER( p , k , newNo , CC , true );
		if( CC[maxno].empty() ) maxno--;
	    }
	}
	//leef_sort( R );
    }
    void MCR(vector<int> &maxclique,int &maxsize){
	pk = 0;
	vector<int> R(n);
	iota( R.begin() , R.end() , 0 );
	map<int,int> No ;
	Extend_Sort( R , No );
	expand( R , No  );
	for(auto i:QMAX) maxclique.push_back( i );
	maxsize = maxclique.size();
	if( EXACT_CLIQUE( maxclique ) )cout<<"Program is Successfully . This CLIQUE IS TRUE !!"<<endl;
	else cout<<"Maybe MISS."<<endl;
    }
    void NUMBER_SORT( vector<int> &R , map<int , int > &No ){
	vector<set<int> > CC( R.size() + 2 );//場合によっては引数で渡す方が良いかも
	int maxno = 0;
	CC[1].clear();
	for(int i=0;i<R.size();i++ ){
	    int p = R[i];
	    int k =  1;
	    while( cut1( p, CC[k] ) )k++;
	    if( k > maxno ){
		maxno = k ;
		CC[maxno].clear();
	    }
	    No[p] = k;
	    CC[k].insert( p );
	    //R.erase( R.begin() );
	}
	int i = 0;
	vector<int> Rp( R.size() );
	for(int k = 1;k<=maxno ; k++){
	    for(auto j:CC[k]){
		Rp[i++] = j;
	    }
	}
	if( i!= R.size() ){
	    cout<<"LACK"<<endl;
	    cout<<R.size()<<' '<<i<<endl;
	}

	R = Rp;
    }
    void Extend_Sort( vector<int> &U , map<int,int> &No ){
	int DeltaG = 0;//グラフの次数
	//[SORT]
	int j = U.size()-1;//i--;
	vector<int> R = U ;
	vector<int> Rmin;
	set_exdegrees( R );
	int mid = 1e9;
	for(int i=0;i<R.size();i++) mid = min( mid , V[ R[i] ].d ) , DeltaG = max( DeltaG , V[ R[i] ].d ) ;
	for(int i=0;i<R.size();i++) if( V[ R[i] ].d == mid ) Rmin.push_back( R[i] );
	while( R.size() != Rmin.size() ){
	    int p = Rmin[0];
	    if( Rmin.size() >= 2 ){
		for(int i=1;i<Rmin.size();i++)if( V[p].exd > V[ Rmin[i] ].exd ) p = Rmin[i];
	    }else{
		p = Rmin[0];
	    }
	    U[j--] = p;
	    for(int i=0;i<R.size();i++)if( R[i] == p ){ R.erase( R.begin() + i );break;}
	    for(int i=0;i<R.size();i++){
		if( mat[ R[i] ][p] ) V[ R[j] ].d--;
	    }
	    set_exdegrees( R , true);
	    Rmin.clear();
	    mid = 1e9;
	    for(int i=0;i<R.size();i++) mid = min( mid , V[ R[i] ].d );
	    for(int i=0;i<R.size();i++) if( V[ R[i] ].d == mid ) Rmin.push_back( R[i] );
	}
	//[Regular subgraph]
	NUMBER_SORT( Rmin , No );
	for(int i=0;i<Rmin.size();i++) U[i] = Rmin[i];
	//[NUMBER]
	int m = 0;
	for(int i=0;i<Rmin.size();i++) m = max( m , No[ Rmin[i] ] ) ;
	int mmax = Rmin.size() + DeltaG - m;
	m++;
	j = Rmin.size() ;
	bool flag = true;
	while( j <= mmax ){
	    if( j >= U.size() ) {
		flag = false;
		break;
	    }
	    No[ U[j] ] = m;
	    m++;
	    j++;
	}
	if( flag ) for(int i = mmax+ 1; i<U.size();i++) No[ U[i] ] = DeltaG + 1;
	set_degrees( Rmin );

	for(int i=0;i<Rmin.size();i++)if( V[ Rmin[i] ].d != Rmin.size() - 1 ) return;
	// Rmin は　クリークなので, 
	if( QMAX.size() < Rmin.size() ){
	    set<int> QQ;
	    for(auto i:Rmin ) QQ.insert( i );
	    cout<<"Extend Sort Clique Update.\n Clique size: "<<QQ.size()<<endl;
	    QMAX = QQ;
	}

    }
    void expand( vector<int> &R , map<int , int > &No ){
	while( R.size() ){
	    int p = R[R.size()-1];
	    if( Q.size() + No[p] > QMAX.size() ){
		Q.insert( p );
		vector<int> Rp;
		map<int,int> Nop = No;
		cut2(  R , Rp );
		if( Rp.size() ){
		    NUMBER_SORT( Rp , Nop );
		    pk++;
		    expand( Rp , Nop );
		}else if( Q.size() > QMAX.size() ){
		    cout<<"STEP: "<<pk<<" Clique size: "<<Q.size()<<endl;
		    QMAX = Q;
		}
		Q.erase( p );
	    }else return ;
	    R.pop_back();
	}
    }
    bool EXACT_CLIQUE( vector<int> &R ){
	for(auto i:R)
	    for(auto j:R){
		if( i!=j && !mat[i][j] ) return false;
	    }
	return true;
    }

};


void read_dimacs( string name , vector<vector<bool> > &conn , int &size){
    ifstream f( name.c_str() );
    string buffer;
    set<int> v;
    multimap<int,int> e;
    while( !getline( f,buffer).eof() ){
	if( buffer[0] == 'e'){
	    int vi , vj ;
	    sscanf(buffer.c_str(),"%*c %d %d", &vi , &vj);
	    v.insert( vi );
	    v.insert( vj );
	    e.insert( make_pair( vi , vj ) );
	}
    }
    size = *v.rbegin() + 1;
    conn = vector<vector<bool> >( size , vector<bool>( size ,false) );
    for( auto it = e.begin(); it != e.end() ; it++){
	conn[it->first][it->second] = true;
	conn[it->second][it->first] = true;
    }
    //cout<<"|E| = "<<e.size()<<" |V| = "<<v.size()<<" p = "<< (double) e.size()/ ( v.size() * (v.size()-1)/2 )<<endl;
    f.close();
}

int main(int argc,char *argv[]){
    string name;
    if( argc == 2 ){
	name = argv[1];
    }else{
	cin>>name;
    }
    cout<<"filename :"<<name<<endl<<endl;;

    vector<vector<bool> > conn;
    int size;
    read_dimacs( name , conn , size);
    clock_t st1 = time( NULL);
    clock_t st2 = clock();
    vector<int> qmax;
    int qsize = 0;
    cout<<"MAX CLIQUE"<<endl<<endl;
    Graph m( conn , size );
    m.MCR( qmax , qsize );
    cout<<"MAXIMUM_CLIQUE : "<<qsize<<endl;
    for(auto i:qmax)cout<<i<<' ';
    cout<<endl;
    cout<<"TIME :"<<((double) (clock()-st2) )/CLOCKS_PER_SEC<<endl<<endl;;
   

    return 0;
}

