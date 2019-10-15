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
	    Vertex(int ii):i(i),d(0){}
	};
	vector< Vertex > v;
	int sz;
	static bool desc_degree(const Vertex &vi ,const Vertex &vj ){ return vi.d > vj.d ; }
	Vertices(){ v.clear() , sz = 0; } 
	void dispose() { v.clear(); }
	void sort() { std::sort( v.begin() , v.end() , desc_degree ); }
	void init_colors(); //
	void set_degrees( Maxclique & );//
	int size(){ return sz; }
	void push( int ii ){ v.push_back( Vertex(ii) ),sz++; }
	void pop(){ v.pop_back() , sz--; }
	Vertex& at( int ii){ return v[ii]; }
	Vertex& end() { return v[sz-1]; }//v.back() ???
    };
    struct ColorClass{
	vector<int> i;
	int sz;
	ColorClass() : sz(0){ i.clear(); }
	void push( int ii ){ i.push_back( ii ) , sz++ ; }
	void pop(){ i.pop_back(), sz--; }
	int size(){ return sz; }
	int& at( int ii ){ return i[ii]; }
	ColorClass& operator = ( ColorClass &dh ){
	    for(int j=0;j<dh.sz;j++) i[j] = dh.i[j];
	    sz = dh.sz;
	    return *this;
	}
    };
    struct StepCount{
	int i1,i2;
	void inc_i1(){ i1++; }
    };
    Vertices V;
    ColorClass Q,Q_MAX;
    vector<ColorClass> C;
    vector<StepCount> S;
    bool connection(int i,int j){ return e[i][j]; }
    bool cut1(int ,ColorClass &);//
    void cut2( Vertices& , Vertices& );//
    void color_sort( Vertices& );//
    void expand( Vertices );//
    void expand_dyn( Vertices );//
    void _mcq( vector<int> & , int , bool );//
    void degree_sort( Vertices &R ){ R.set_degrees( *this ) , R.sort() ; }
    //public
    Maxclique( vector<vector<bool> > , int , float = 0.025 );
    int steps(){ return pk; }
    void mcq( vector<int> &maxclique , int sz ){ _mcq( maxclique , sz , false ) ; }
    void mcqdyn( vector<int> &maxclique , int sz ){ _mcq( maxclique , sz , true ); }
    ~Maxclique(){
	C.clear();
	S.clear();
	V.dispose();
    }
};

int main(){

    return 0;
}

