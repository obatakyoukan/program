#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

struct Graph{
    ll n;
    pair< ll , vector<ll> > Q_MAX;// Maximum Clique
    vector<vector<bool> > mat;
    Graph(){}
    Graph( ll n ):n(n){
	mat = vector<vector<bool> >( n ,vector<bool>(n,false) );
    }
    void add_edge(ll a,ll b){
	mat[a][b] = true;
	mat[b][a] = true;
    }
    struct Color{
	ll sz, i ;
	vector<ll> array;
	Color():sz(0),i(0){ array = vector<ll>(0); };
	//Color( ll sz ):sz(sz),i(0){ array = vector<ll> ( sz ) ; }
	//void push( ll ii ){ array[ i++ ] = ii; }//
	//void pop(){ i-- };// 
	void push(ll ii ){ array.push_back( ii ),sz++; }
	void pop(){ array.pop_back(),sz--; }
	ll size(){ return array.size(); }
	ll& at(ll ii ){ return array[ii]; }
	Color& operator=(Color &dh){
	    array.clear();
	    for(ll j=0;j<dh.size();j++) array.push_back( dh.array[j] );
	    sz = dh.sz;
	    return *this;
	}
    };

    struct StepCount{
	ll i1,i2;
	StepCount():i1(0),i2(0) {}
    };

};

int main(){

    return 0;
}

