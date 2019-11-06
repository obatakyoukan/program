#include <iostream>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <vector>
#include <cstring>
#include <string.h>
#include <fstream>
#include <cmath>
using namespace std;

struct Maxclique {
  bool** e;
  int pk;
  struct Vertices {
    struct Vertex {
      int i, d;
      void set_i(const int ii)  { i = ii; }
      int get_i() const { return i; }
      void set_degree(int dd) { d = dd; }
      int get_degree() const { return d; }
      void set(const int ii , const int dd ){ i = ii , d = dd; }
      void set( Vertex &v ){ set( v.i , v.d ); }
      Vertex& operator=(const Vertex& v){
	  set(v.i , v.d);
	  return *this;
      }
    };
    Vertex *v;
    int sz;
    static bool desc_degree(const Vertex vi, const Vertex vj) { return (vi.get_degree() > vj.get_degree()); }
    Vertices():sz(0){}
    Vertices(int size) : sz(0) { v = new Vertex[size]; }
    ~Vertices () {}
    void dispose() { if (v) delete [] v; }
    void sort() { std::sort(v, v+sz, desc_degree); }
    void set_degrees(Maxclique&);
    int size() const { return sz; }
    void rewind(){ sz = 0; }
    void push(const int ii) { v[sz++].set_i(ii); };
    void push(const int ii,const int dd ){ v[sz++].set(ii,dd); }
    void push( Vertices::Vertex &p){ push( p.i , p.d ); }
    void pop() { sz--; };
    void erase(int i){//ここ直したい
	for(int j = i+1;j<size();j++){
	    swap( v[j] , v[j-1] );
	    //v[j-1] = v[j];
	}
	pop();
    }
    void erase_p(int p ){
	for(int i=0;i<size();i++)if( v[i].i == p ){ erase(i); return ; }
    }
    void erase( Vertices::Vertex &p ){ erase_p( p.i ); }
    void roll( ){
	Vertex p = v[0];
	for(int i=0;i<size()-1;i++) v[i] = v[i+1];
	v[size()-1] = p;
    }
    Vertex& at(const int ii) const { return v[ii]; }
    Vertex& end() const { return v[sz - 1]; }
    Vertex& operator[] (int i){ return v[i]; }
    Vertices& operator = (  Vertices& dv ){
	v = new Vertex[ dv.size() ];
	sz = 0;
	//cout<<"KKK"<<endl;
	//for(int j=0;j<dv.size();j++) v[j].set( dv.v[j] );
	for(int j=0;j<dv.size();j++) push( dv.v[j]);
	//sz = dv.sz;
	return *this;
    }
  };
  struct ColorClass {
    int *i;
    int sz;
    ColorClass() : sz(0), i(0) {}
    ColorClass(const int sz) : sz(sz), i(0) { init(sz); }
    ~ColorClass() { if (i) delete [] i;
    }
    void init(const int sz) { i = new int[sz]; rewind(); }
    void push(const int ii) { i[sz++] = ii; };
    void pop() { sz--; };
    void erase(int ii ){
	for(int j = ii + 1; j <= size();j++){
	    swap( i[j] , i[j-1] ) ; 
	    //i[j-1] = i[j];
	}
	pop();
    }
    void erase_p( int p ){
	for(int j=0;j<size();j++)if( i[j] == p ){
	    erase(j);
	    return;
	}
    }
    void rewind() { sz = 0; };
    int size() const { return sz; }
    int& at(const int ii) const { return i[ii]; }
    ColorClass& operator=(const ColorClass& dh) {
      for (int j = 0; j < dh.sz; j++) i[j] = dh.i[j];
      sz = dh.sz;
      return *this;
    }
  };
  Vertices V;
  ColorClass *C;
  std::set<int> Q,QMAX;
  
  int *change;
  void trance(int ii , int jj ){
      for(int i=0;i< V.size();i++){
	  swap( e[ii][i] , e[jj][i] );
	  swap( e[i][ii] , e[i][jj] );
      }
  }

  bool connection(const int i, const int j) const { return e[i][j]; }
  bool cut1(const int, const ColorClass&);
  vector<int>  cut1_1(const  int ,const  ColorClass&);
  void cut2(const Vertices&, Vertices&);
  void cut2(int , Vertices&, Vertices&);
  void color_sort(Vertices&);
  Maxclique(bool**, const int);
  int steps() const { return pk; }
  ~Maxclique() {
    if (C) delete [] C;
    V.dispose();
  };
  void init_lb( Vertices&);
  void init_lb( Vertices& , bool );
  void RE_COLOR( int , int );
  void NUMBER_SORT( Vertices& , map<int,int>&);
  void NUMBER_SORT_R( Vertices& , Vertices& , map<int,int> &No ); 
  void EXTEND_SORT(Vertices& , map<int,int>&  , bool);
  void expand( Vertices& , map<int,int>& );//MCR用
  void expand( Vertices& , Vertices& , map<int,int>& );
  void MCS(vector<int>& , int&);
  void MCR(vector<int>& , int&);
};

void Maxclique::init_lb( Vertices& R ){
    Vertices Rp;
    Rp = R;
    Rp.set_degrees( *this );
    set<int> QQ = Q;
    int cnt = 2*( sqrt( R.size() + 1 ) );
    cout<<"init_lb times alpha=2sqrt(V): "<<cnt<<endl;
    for(int i=0;i<cnt;i++){
	Vertices Rpp;
	Rpp = Rp;
	Q.clear();
	init_lb( Rpp , false );
	Rpp.dispose();
	Rp.roll();
    }
    Q = QQ;
}
void Maxclique::init_lb( Vertices& R , bool flag ){
    Vertices::Vertex p = R[0];
    if( flag ){
	for(int i=0;i<R.size();i++)if( R[i].d > p.d ) p = R[i];
    }
    Vertices Rp(R.size());
    Q.insert( p.i );
    cut2( p.i , R , Rp );
    R.dispose();
    R = Rp;
    Rp.dispose();
    int md = 0;
    for(int i=0;i<R.size();i++)if( connection( p.i , R[i].i ) ) R[i].d--, md = max( md , R[i].d );
    if( R.size() == 0 ){
	if( Q.size() > QMAX.size() ){
	    cout<<"init_lb update clique. clique size: "<<Q.size()<<endl;
	    QMAX = Q;
	}
	return;
    }
    if( md + Q.size() >= QMAX.size() ){
	init_lb( R , true );
    }

}
void Maxclique::Vertices::set_degrees(Maxclique &m){
  for(int i=0;i<size();i++){
    int d = 0;
    for(int j=0;j<size();j++){
      if( m.connection(v[i].i , v[j].i) ) d++;
    }
    v[i].d = d;
  }
}

bool Maxclique::cut1(const int pi, const ColorClass &A) {
  for (int i = 0; i < A.size(); i++)
      if (connection(pi, A.at(i)))
        return true;
  return false;
}
vector<int> Maxclique::cut1_1(const int p , const  ColorClass &A){
  vector<int> res;
  for(int i=0;i<A.size();i++){
    if( connection( p , A.at(i) )  ) res.push_back( A.at(i) );
  }
  return res;
}
void Maxclique::cut2(const Vertices &A, Vertices &B) {
for (int i = 0; i < A.size() - 1; i++) {
    if (connection(A.end().get_i(), A.at(i).get_i()))
      B.push(A.at(i).get_i());
  }
}
void Maxclique::cut2(int p , Vertices &A , Vertices &B ){
  for(int i=0;i<A.size();i++){
    if( connection( p , A.at(i).i ) ) B.push( A.at(i).i  );
  }
}
Maxclique::Maxclique ( bool** conn, const int sz) : pk(0) , V(sz) {
  assert(conn!=0 && sz>0);
  for (int i=0; i < sz; i++) V.push(i);
  change = new int[sz+1];
  for(int i=0;i<sz;i++) change[i] = i;
  e = conn;
  C = new ColorClass[sz + 1];
  for (int i=0; i < sz + 1; i++) C[i].init(sz + 1);
}

void Maxclique::NUMBER_SORT( Vertices &R , map<int,int> &No){
  //[ NUMBER ]
  int maxno = 0;
  //cout<<"start"<<R.size()<<endl;
  C[1].rewind();
  C[2].rewind();
  //for(int i=0;i<R.size();i++){
  while( R.size() ){
    //int p = R[i].i;
    int p = R.end().i;
    int k = 1;
    while ( cut1(p,C[k]) ) k++;
    if( k > maxno ){
      maxno = k;
      //C[k].rewind();
      C[k+1].rewind();
    }
    No[p]=k;
    C[k].push(p);
    //R.erase_p(p);
    R.pop();
  }
  //[ SORT ]
  //int i = 0;
  //R.rewind(); //これでもいいかも
  for( int k = 1 ; k <= maxno ; k++ ){
    for( int j = 0 ; j < C[k].size() ; j++ ){
      R.push( C[k].at(j) );
      //i++;
    }
  }
  //cout<<"end"<<R.size()<<endl;
}
void Maxclique::RE_COLOR(int p , int pcol){
  int cutc = QMAX.size() - Q.size();
  for(int k1 = 1; k1 < cutc ; k1++){
    vector<int> qq = cut1_1(p,C[k1] );
    if( qq.size() == 1 ){
      int q = qq[0];
      for(int k2 = k1 + 1 ; k2 <= cutc ; k2++ ){
        if( !cut1( q , C[k2] ) ){
          C[pcol].erase( p );
          C[k1].erase( q );
          C[k1].push( p );
          C[k2].push( q );
          return;
        }
      }
    }
  }
}
void Maxclique::NUMBER_SORT_R( Vertices &Vs , Vertices &R , map<int,int> &No){
  R = Vs;
  //[ NUMBER ]
  int kmax = 1;
  int cutc = QMAX.size() - Q.size();
  C[1].rewind();
  C[2].rewind();
  for(int i=0;i<Vs.size();i++){
    Vertices::Vertex p = Vs[i];
    int k = 1;
    while( cut1( p.i , C[k] ) )k++;
    if( k > kmax ){
      kmax = k;
      C[kmax].rewind();
      C[kmax+1].rewind();
    }
    C[k].push( p.i );
    // == RE-COLOR start ==
    if( k > cutc && k == kmax){
      RE_COLOR( p.i , k );
      if( C[kmax].size() == 0  )kmax--;
    }
    // == RE-COLOR end ==
  }
  // [ SORT ]
  int i = Vs.size()-1;
  if( cutc < 0 ) cutc = 0;
  for(int k = kmax ; k>=cutc + 1 ; k-- ){
    for(int j = C[k].size()-1 ; j>=0 ; j-- ){
      R[ i ].i = C[k].at(j); 
      No[ R[i].i ] = k;
      i--;
    }
  };
  // i != 0 -> i != -1
  if( i != -1 ) No[ R[i].i ] = cutc;
}
void Maxclique::EXTEND_SORT( Vertices &U , map<int,int> &No , bool is_init = false){
  int DeltaG = 0;
  //[ SORT ]
  int ii = U.size() - 1;
  //Vertices R = U; //これはダメ
  Vertices R;
  R=U;
  //Vertices R(U.size() );
  //for(int i=0;i<U.size();i++)R.push( U[i] );
  R.set_degrees( *this );
  int mid = 1e9;
  for(int i=0;i<R.size();i++) mid = min( mid , R[i].d ) , DeltaG = max( DeltaG , R[i].d );
  Vertices Rmin( R.size() );
  for(int i=0;i<R.size();i++) if( R[i].d == mid ) Rmin.push( R[i] );
  
  /*cout<<"Init State"<<R.size()<<endl;
  int rinitsize = R.size();
  for(int i=0;i<rinitsize;i++)cout<<R[i].i<<' '; 
  cout<<endl;*/

  while( R.size() != Rmin.size() ){
    int p = Rmin[0].i;
    if( Rmin.size() >= 2 ){//p := a vertex in Rmin such that ex-deg(p) = Min{ex-deg(q) | q ∈ Rmin}
      int mexd = 0;
      //for(int i=0;i<Rmin.size();i++)if( connection( p , Rmin[i].i ) ) mexd+= Rmin[i].d;
      for(int i=0;i<R.size();i++)if( connection( p , R[i].i ) ) mexd+= R[i].d;
      for(int i=1;i<Rmin.size();i++){
        int exd = 0;
        //for(int j=0;j<Rmin.size();j++)if( connection( Rmin[i].i , Rmin[j].i ) ) exd += Rmin[j].d;
        for(int j=0;j<R.size();j++)if( connection( Rmin[i].i , R[j].i ) ) exd += R[j].d;
        if( mexd > exd ){
          mexd = exd;
          p = Rmin[i].i;
        }
      }
    }
    R.erase_p(p);
    U[ii].i = p;
    ii--;
    for(int i=0;i<R.size();i++){// ここを治す必要あるかも
      if( connection( p , R[i].i) )R[i].d--;
    }
    //R.set_degrees(*this);
    mid = 1e9;
    for(int i=0;i<R.size();i++) mid = min( mid , R[i].d );
    Rmin.rewind();
    for(int i=0;i<R.size();i++) if( R[i].d == mid ) Rmin.push( R[i] );
  }
  //[ Regular subgraph ]
  NUMBER_SORT(Rmin,No);
  for(int i=0;i<Rmin.size();i++) U[i] = Rmin[i];
  //[ NUMBER ]
  int m = 0;
  for(int i=0;i<Rmin.size();i++) m = max( m , No[ Rmin[i].i ] );
  int mmax = Rmin.size()  + DeltaG  - m ;
  m++;
  ii = Rmin.size();
  bool GotoSTART = false;
  while( ii <= mmax ){
    if( ii > U.size() ){ 
      GotoSTART = true;
      break;
    }
    No[ U[ ii ].i ] = m;
    m++;
    ii++;
  }
  if( !GotoSTART ){
    for( ii = mmax + 1 ; ii < U.size() ; ii++ ) No[ U[ii].i ] = DeltaG + 1;
  }
  // RE_BUILD_C ????
  //
  //
  // ここがいるかはわからない
  for(int i=0;i<=max( m , DeltaG );i++){
      C[i].rewind();
  }
  for(int i=0;i<U.size();i++)C[ No[ U[i].i ] ].push( U[i].i );
  //
  //
  //
  if( !is_init ) return;
  Rmin.set_degrees(*this);
  for(int i=0;i<Rmin.size();i++)if( Rmin[i].d != Rmin.size() - 1) return;
  if( QMAX.size() < Q.size() + Rmin.size() ){
    set<int> QQ = Q;
    for(int i=0;i<Rmin.size();i++)QQ.insert( Rmin[i].i );
    cout<<"EXTEND SORT Clique Update. \n Clique Size: "<<QQ.size()<<endl;
    QMAX = QQ;
  }
}

void Maxclique::MCR( vector<int> &maxclique , int& maxsize ){
  pk = 0;
  Vertices R;
  R = V;
  map<int,int> No;
  EXTEND_SORT( R , No , true );
  expand( R , No );
  for(auto i:QMAX){
    maxclique.push_back( i );
  }
  maxsize = maxclique.size();
}

void Maxclique::MCS(vector<int> &maxclique, int &maxsize){
  pk = 0;
  Vertices R;
  R = V;
  map<int,int> No;
  EXTEND_SORT( R , No , true );// MCRのグラフの再構成およびNoの付与
  init_lb( R );
  cout<<"oringinal Graph"<<endl;
  for(int i=0;i<R.size();i++){
      for(int j=0;j<R.size();j++){
	  if( connection(i,j) )cout<<1;
	  else cout<<0;
      }
      cout<<endl;
  }
  cout<<endl;
  //Graphの再構成　今度書いてみる
  Vertices RES;
  RES = R;
  for(int i=1;i<=R.size();i++)C[i].rewind();
  for(int i=0;i<R.size();i++){
      change[i] = R[i].i;
      trance( i , R[i].i );
      C[ No[ R[i].i ] ] = i;
  }
  map<int,int> newNo = No;
  for(int i=0;i<R.size();i++) newNo[i] = No[ R[i].i ] , R[i].i = i;
  No.clear();

  Vertices Rp;
  Rp = R;
  

  cout<<"changing Graph"<<endl;
  for(int i=0;i<R.size();i++){
      for(int j=0;j<R.size();j++){
	  if( connection(i,j) )cout<<1;
	  else cout<<0;
      }
      cout<<endl;
  }
  cout<<endl;

  expand( R , Rp , newNo );
  
  R = RES;
  for(int i=0;i<R.size();i++){
      change[i] = R[i].i;
      trance( i , R[i].i );
  }
  RES.dispose();

  //Graphを戻す
  for(auto i:QMAX){
    maxclique.push_back( i );
  }
  maxsize = maxclique.size();
}

//MCR用
void Maxclique::expand(Vertices &R , map<int,int> &No ){//これを試したい
    while( R.size() ){
	Vertices::Vertex p = R.end();
	if( Q.size() + No[ p.i ] > QMAX.size() ){
	    Q.insert( p.i );
	    Vertices Rp( R.size() );
	    cut2( R , Rp );
	    if( Rp.size() ){
		map<int,int> Nop;// initial value of Nop has no significance
		NUMBER_SORT( Rp , Nop );
		pk++;
		expand( Rp , Nop );
		Nop.clear();
	    }else if( Q.size() > QMAX.size() ){
        	cout<<"Number of Steps: "<<pk<<"  Clique Update. Size: "<<Q.size()<<endl;
        	QMAX = Q;
	    }
	    Q.erase( p.i );
	    Rp.dispose();
	}else return;
	R.pop();
    }
}

void Maxclique::expand(Vertices &Vs , Vertices &R , map<int,int> &No){
  int cutc = QMAX.size()-Q.size();
  while( R.size() ){
    Vertices::Vertex p = R.end();// the last Vertex in R
    if( Q.size() + No[ p.i ] >  QMAX.size() ){
    //if( Q.size() + R.size() >  QMAX.size() ){
      Q.insert( change[p.i] );
      Vertices Vp( Vs.size() );
      cut2( p.i , Vs , Vp );
      //cut2( Vs , Vp );
      if( Vp.size() ){
        Vertices newR;
        map<int , int > newNo;
        NUMBER_SORT_R( Vp , newR , newNo );// Initial value dosen't matter. newR ,newNo
        //
	/*cout<<"CUTC "<<cutc<<endl;
	for(int i=0;i<newR.size();i++) if( newNo.find(newR[i].i ) != newNo.end() )cout<<"("<<newR[i].i<<","<<newNo[ newR[i].i ]<<") ";
	cout<<endl;*/
	pk++;
	expand( Vp , newR , newNo );
        newR.dispose();//必要?
        newNo.clear();//必要？
      }else if( Q.size() > QMAX.size() ){
        cout<<"Number of Steps: "<<pk<<"  Clique Update. Size: "<<Q.size()<<endl;
        QMAX = Q;
      }
    }
    else return ;
    Q.erase(change[p.i]);
    R.pop();
    Vs.erase_p(p.i);
  }
}


void read_dimacs(string name, bool** &conn, int &size) {
  ifstream f (name.c_str());
  string buffer;
  assert(f.is_open());
  set<int> v;
  multimap<int,int> e;
  while (!getline(f, buffer).eof()) {
    if (buffer[0] == 'e') {
      int vi, vj;
      sscanf(buffer.c_str(), "%*c %d %d", &vi, &vj);
      v.insert(vi);
      v.insert(vj);
      e.insert(make_pair(vi, vj));
    }
  }
//  size = v.size() + 1;
  size = *v.rbegin() + 1;
  conn = new bool*[size];
  for (int i=0; i < size; i++) {
    conn[i] = new bool[size];
    memset(conn[i], 0, size * sizeof(bool));
  }
  for (multimap<int,int>::iterator it = e.begin(); it != e.end(); it++) {
    conn[it->first][it->second] = true;
    conn[it->second][it->first] = true;
  }
  cout << "|E| = " << e.size() << "  |V| = " << v.size() << " p = " << (double) e.size() / (v.size() * (v.size() - 1) / 2) << endl;
  f.close();
}
  

//CheckList 
//MCS EXPAND
//まずはeraseを治す消したい奴ではなく最後の要素を消してなぜか消したい要素が最後に来ている?????????????????????????
//Vertices の代入演算子の実装が必要そう
//今はただポインタを共有しているせいで上手く別々に変更することができていない??
//次はR などの中身をint のみで管理するように設計し, 先にint を管理する Vecrorで動くかをみたい
// Vertices V のみで　R は　int ( V[index] の　index の値で管理する )
// Vertices R = V; はダメ　 => Vertices R; R = V ; ならいい????
//とりあえずEXTEND_SORTは良さそう
// cut2( Vs , Vp ) => cut2( p.i , Vs , Vp )
// 
// next: init_lbの実装 => 完了
// Vertices 演算子=  sz = 0を追記
//init lb 逆に遅い???
//
int main(int argc , char *argv[] ){
    bool **conn;
    int size;
    cout<<"Filename : "<<argv[1]<<endl;
    read_dimacs( argv[1] , conn , size );
    clock_t st1 = clock();
    Maxclique m(conn , size );
    vector<int> maxclique;
    int maxsize;
    cout<<"MCS START"<<endl;
    m.MCS( maxclique , maxsize );
    cout<<"Max size = "<<maxsize<<endl;
    cout<<"Maximum Clique : ";
    for(int i=0;i<maxsize;i++)cout<<maxclique[i]<<' ';
    cout<<endl;
    cout<<"Number of Steps = "<<m.steps()<<endl;
    cout<<"Time = "<<( (double) ( clock() - st1 ) )/ CLOCKS_PER_SEC <<endl;
    return 0;
}
