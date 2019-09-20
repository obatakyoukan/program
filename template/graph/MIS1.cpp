#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

// 謎のバグがあるhttps://atcoder.jp/contests/code-thanks-festival-2017-open/submissions/me 2,3回目の提出
// 隣接行列形式はMIS1_mat.cpp , MIS1_1_mat.cpp
//
/*
struct state{
    ll  n;
    vector<ll> s;
    state(ll n):n(n){
	s = vector<ll>(n/64 + 1 ,0);
    }



};*/

struct Graph{
    ll n;
    vector<vector<ll> > g;//隣接リスト
    vector<ll> d;//degree
    vector<bool> used;
    //初期化
    Graph(){}
    Graph(ll n):n(n){
	g = vector<vector<ll> >(n);
	d = vector<ll>(n,0);
    }
    
    void add_edge(ll a,ll b){
	g[a].push_back(b);
	g[b].push_back(a);
	d[a]++;
	d[b]++;
    }

    ll MIS1(){
	used = vector<bool>(n,true);
	vector<ll> rest(n);
	iota(rest.begin(),rest.end(),0);//0~n-1まで生成
	return MIS1(rest,0);
    }

    ll MIS1(vector<ll> &rest,ll cnt){
	/*cout<<"rest : "<<rest.size()<<" count: "<<cnt<<endl;
	for(auto i:rest){
	    cout<<"("<<i<<","<<d[i]<<") ";
	}
	cout<<endl;*/
	if(rest.size() == 0) return 0;
	vector<ll> md;
	ll minid = n;//最小次数 
	ll minindex = n-1;
	ll res = 0;
	set<ll> st0;
	for(ll i=0;i<rest.size();i++){//最小次数決定
	    //minid = min(minid,d[ rest[i] ] );
	    if( minid >= d[ rest[i] ] ){
		minid = d[ rest[i] ];
		minindex = rest[i];
	    }
	    if( d[ rest[i] ] == 0 ){
		st0.insert( rest[i] );
		//used[ rest[i] ] = false;
	    }
	}
	if( minid == 0 ){//Case:次数0  exists
	    vector<ll> next;
	    res += st0.size();
	    for(ll i=0;i<rest.size();i++){
		if( st0.find( rest[i] ) == st0.end() ){
		    next.push_back( rest[i] );
		}
	    }
	    return res + MIS1(next,cnt+res);
	}
	// Case minimum degree is not 0
	// I wish else case will be extended .  
	vector<ll> nei;
	nei.push_back( minindex );
	for( auto it:g[minindex] ){
	    if( *lower_bound(rest.begin() , rest.end() , it ) == it  ){//find
		nei.push_back( it );
	    }
	}
	//cout<<nei.size()<<endl;
	for( auto it:nei ){
	    set<ll> st;//削除点
	    st.insert(it);
	    for( auto i:g[it]){//隣接点 restに含まれるなら
		if( *lower_bound(rest.begin() , rest.end() , i ) == i ) st.insert( i );
	    }
	    vector<ll> next;
	    for( auto i:rest ){
		if(st.find( i ) == st.end() ){// not find
		    next.push_back(i);
		}
	    }
	    //削除する隣接点の次数を下げることを書く
	    //
	    for(auto i:st){
		for(auto j:g[i]){//削除点の隣接点
		    //  cout<<j<<endl;
		    if(*lower_bound(rest.begin(),rest.end(),j) == j )d[j]--;
		}
	    }
	   // cout<<"delete: "<<it<<endl;
	    res = max(res,MIS1(next,cnt+1) );
	    //削除する隣接点の次数を戻す
	    //
	    for(auto i:st){
		for(auto j:g[i]){//削除点の隣接点
		    if(*lower_bound(rest.begin(),rest.end(),j) == j)d[j]++;
		}
	    }
	}

	return 1 + res;
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
    //cerr<<"Graph Generated."<<endl;
    cout<<g.MIS1()<<endl;
    return 0;
}

