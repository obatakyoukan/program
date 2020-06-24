#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

//行列形式(mat)
//Max Independent Set(MIS)
//Maximum Clique
//
// できれば隣接リスト形式でかけるようにする
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
	return Complement().MIS1();
    }
    ll SubDegree(vector<ll> &rest, ll a){
	ll res = 0;
	for(auto i:rest){
	    if(mat[a][i])res++;
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
    ll MIS1(){
	vector<ll> rest(n);
	iota( rest.begin() , rest.end() , 0 );
	return MIS1(rest);
    }

    ll MIS1(vector<ll> &rest){
	ll res = 0;
	if(rest.size() == 0) return 0;
	ll mind = 2*n,mini = n-1;
	set<ll> st0,st1;
	for(auto i:rest){
	    ll di = SubDegree(rest,i);
	    if( mind > di ){
		mind = di;
		mini = i;
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
	    return res + MIS1( next );
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
	    
	    return MIS1(sub) + MIS1(subrest);
	}
	// Case: minimum degree is else
	// I want elsecase to extend
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
	    res = max(res,MIS1(next) );
	    //削除する隣接点の次数を戻すときかく
	}
	return 1+res;
    }

    
};


int main(){
    char tmp;
    cin>>tmp>>tmp;
    ll n,m;
    cin>>n>>m;
    Graph g(n);
    for(ll i=0;i<m;i++){
	ll a,b;
	cin>>tmp>>a>>b;
	a--,b--;
	g.add_edge(a,b);
    }
    cout<<g.Maximum_Clique()<<endl;
    return 0;
}

