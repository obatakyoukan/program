#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
typedef pair<mp,ll> mmp;
#define Th1 0.4
#define Th2 0.1
ll inf =  1e9;

struct Graph{
    ll n;
    set<ll> Q_MAX;
    vector<vector<bool> > mat;
    vector<set<ll> > g;
    vector<ll> degree;
    Graph(){}
    Graph( ll n ):n(n){
	g = vector< set<ll> >( n );
	degree = vector<ll>(n,0);
	mat = vector<vector<bool> >( n ,vector<bool>(n,false) );
    }
    void add_edge( ll a, ll b ){
	mat[a][b] = mat[b][a] = true;
	degree[a]++; 
	degree[b]++;
	g[a].insert( b );
	g[b].insert( a );
    }
    vector<ll> Intersection( vector<ll> &R , ll p ){
	vector<ll> res;
	for( auto i:R ) if( i != p && g[p].find( i ) != g[p].end() ) res.push_back( i );
	return res;
    }
    pair< vector<ll> , map<ll,ll> > Intersection( vector<ll> &R , map<ll,ll> &No , ll p ){
	vector<ll> newR;
	map<ll ,ll> newNo;
	for( auto i:R ){
	    if( i != p && g[p].find( i ) != g[p].end() ){
		newR.push_back( i );
		newNo[i] = No[i];
	    }
	}
	return pair< vector<ll> , map<ll,ll> >( newR , newNo );
    }
    set<ll> Intersection( set<ll> &R , ll p ){
	set<ll> res;
	for( auto i:R ){
	    if( i != p && g[p].find( i ) != g[p].end() ) res.insert( i );
	}
	return res;
    }
    ll SubDegree( vector<ll> &R ,ll p ){
	ll res = 0;
	for( auto i:R )if( mat[p][i] ) res ++;
	return res;
    }
    ll No_MAX(vector<ll> &R , map<ll,ll> &No){

    }

}


int main(){

    return 0;
}

