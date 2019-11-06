#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

struct Maxclique{
    vector<vector<bool> > e;
    int pk,level;
    float Tlimit;
    struct Vertices{
	struct Vertex{
	    int i,d;//index ? ,degree
	    Vertex(int i):i(i),d(0){}
	    Vertex(int i,int d):i(i),d(d){}
	};
	vector< Vertex > v;
	int sz;
	static bool desc_degree(const Vertex &vi ,const Vertex &vj ){ return vi.d > vj.d ; }
	Vertices(){ v.clear() , sz = 0; } 
	void dispose() { v.clear(); }
	void sort() { std::sort( v.begin() , v.end() , desc_degree ); }
	void init_colors(){
	    int max_degree = v[0].d;
	    for(int i=0;i<max_degree;i++) v[i].d = i+1;
	    for(int i=max_degree;i<sz;i++) v[i].d = max_degree + 1;
	}//
	void set_degrees( Maxclique &m ){
	    for(int i=0;i<sz;i++){
		int d = 0;
		for(int j=0;j<sz;j++){
		    if( m.connection( v[i].i , v[j].i ) ) d++;
		    v[i].d = d;
		}
	    }
	}//
	//int size(){ return sz; }
	int size(){ return v.size();}
	void push( int ii ){ v.push_back( Vertex(ii) ),sz++; }
	void pop(){ v.pop_back() , sz--; }
	Vertex& at( int ii){ return v[ii]; }
	Vertex& end() { return v[size()-1]; }//v.back() ???
    };
    struct ColorClass{
	vector<int> i;
	int sz;
	ColorClass() : sz(0){ i.clear(); }
	void push( int ii ){ i.push_back( ii ) , sz++ ; }
	void pop(){ i.pop_back(), sz--; }
	void rewind(){ i.clear(),sz=0; }
	int size(){ return i.size(); }
	int& at( int ii ){ return i[ii]; }
	ColorClass& operator = ( ColorClass &dh ){
	    for(int j=0;j<size();j++) i[j] = dh.i[j];
	    for(int j=size();j<dh.size();j++) push( dh.i[j] );
	    sz = dh.sz;
	    return *this;
	}
    };
    struct StepCount{
	int i1,i2;
	void inc_i1(){ i1++; }
    };
    Vertices V;
    ColorClass Q,QMAX;
    vector<ColorClass> C;
    vector<StepCount> S;
    bool connection(int i,int j){ return e[i][j]; }
    bool cut1(int pi,ColorClass &A){
	for(int i=0;i<A.size();i++)if( connection( pi , A.at( i ) ) ) return true;
	return false;
    }
    void cut2( Vertices& A, Vertices& B ){
	for(int i=0;i<A.size()-1;i++){
	    if( connection( A.end().i , A.at(i).i ) )B.push( A.at(i).i );
	}
    }
    void color_sort( Vertices& R ){
	int j = 0;
	int maxno = 1;
	int min_k = QMAX.size() - Q.size() + 1 ;//Noth ???
	// ColorClass の直しが必要かも
	C[1].rewind();
	C[2].rewind();
	int k = 1;
	for( int i=0;i<R.size();i++){
	    int pi = R.at(i).i;
	    k = 1;
	    while( cut1(pi,C[k]) ) k++;
	    if( k > maxno ){
		maxno = k ;
		C[ maxno + 1].rewind();
	    }
	    C[k].push( pi );
	    if( k < min_k ){
		R.at(j++).i = pi;;
	    }
	}
	if( j > 0 ) R.at(j-1).d = 0;
	if( min_k <= 0 ) min_k = 1;
	for( k = min_k;k<=maxno;k++){
	    for(int i=0;i<C[k].size();i++){
		R.at(j).i = C[k].at(i);
		R.at(j++).d = k;
	    }
	}
    }
    void expand( Vertices R){
	while( R.size() ){
	    if( Q.size() + R.end().d > QMAX.size() ){
		Q.push( R.end().i );
		Vertices Rp;
		cut2( R, Rp );
		if( Rp.size() ){
		    color_sort( Rp );
		    pk++;
		    expand( Rp );
		}else if( Q.size() > QMAX.size() ){
		    cout<<"Step = "<<pk<<" current max. clique size = "<<Q.size()<<endl;
		    QMAX = Q;
		}
		Rp.dispose();
		Q.pop();
	    }else{
		return ;
	    }
	    R.pop();
	}
    }
    void expand_dyn( Vertices R){
	S[level].i1 =  S[level].i1 + S[level-1].i1 - S[level].i2 ;
	S[level].i2 =  S[level-1].i1;
	while( R.size() ){
	    if( Q.size() + R.end().d > QMAX.size() ){
		Q.push( R.end().i );
		Vertices Rp;
		cut2( R , Rp );
		if( Rp.size() ){
		    if( (float)S[level].i1/++pk < Tlimit ){
			degree_sort( Rp );
		    }
		    color_sort( Rp );
		    S[level].inc_i1();
		    level++;
		    expand_dyn( Rp );
		    level--;
		}else if( Q.size() > QMAX.size() ){
		    cout<<"Step = "<<pk<<" current max. clique size = "<<Q.size()<<endl;
		    QMAX = Q;
		}
		Rp.dispose();
		Q.pop();
	    }else{
		return ;
	    }
	    R.pop();
	}
    }
    void _mcq( vector<int> &maxclique , int &sz, bool dyn){
	V.set_degrees(*this);
	V.sort();
	V.init_colors();
	if( dyn ){
	    for( int i=0; i < V.size() + 1 ; i++){
		S[i].i1 = 0;
		S[i].i2 = 0;
	    }
	    expand_dyn( V );
	}else{
	    expand( V );
	}
	maxclique = vector<int>( QMAX.size() );
	for(int i=0;i<QMAX.size();i++){
	    maxclique[i] = QMAX.at(i);
	}
	sz = QMAX.size();
    }
    void degree_sort( Vertices &R ){ R.set_degrees( *this ) , R.sort() ; }
    //public
    Maxclique( vector<vector<bool> > conn , int sz , float tt= 0.025 ):pk(0),level(1),Tlimit(tt){
	for( int i=0; i < sz ; i++) V.push(i);
	e = conn;
	C = vector<ColorClass>( sz + 1 );
	S = vector<StepCount>( sz + 1 );
    }
    int steps(){ return pk; }
    void mcq( vector<int> &maxclique , int &sz ){ _mcq( maxclique , sz , false ) ; }
    void mcqdyn( vector<int> &maxclique , int &sz ){ _mcq( maxclique , sz , true ); }
    ~Maxclique(){
	C.clear();
	S.clear();
	V.dispose();
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
   // cout<<"PATTERN1:"<<endl<<endl;
    vector<vector<bool> > conn;
    int size;
    read_dimacs( name , conn , size);
    clock_t st1 = time( NULL);
    clock_t st2 = clock();
    vector<int> qmax;
    int qsize = 0;
   // Maxclique m(conn,size);
    
    //m.mcq( qmax , qsize );
    //sort( qmax.begin() , qmax.end() );
    //cout<<"MAXIMUM_CLIQUE : "<<qsize<<endl;
    //for(auto i:qmax)cout<<i<<' ';
    //cout<<endl;
    //cout<<"TIME :"<<((double) (clock()-st2) )/CLOCKS_PER_SEC<<endl<<endl;;

    cout<<"PATTERN2:"<<endl<<endl;
    st2 = clock();
    Maxclique m2( conn , size );
    qmax.clear();
    qsize = 0;
    m2.mcqdyn( qmax , qsize );
    sort( qmax.begin() , qmax.end() );
    cout<<"MAXIMUM_CLIQUE : "<<qsize<<endl;
    for(auto i:qmax)cout<<i<<' ';
    cout<<endl;
    cout<<"TIME :"<<((double) (clock()-st2) )/CLOCKS_PER_SEC<<endl<<endl;;
   
    return 0;
}

