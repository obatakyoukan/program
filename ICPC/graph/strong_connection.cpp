#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
#define MAX_V 10001
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long int ll;
typedef pair<int,int> mypair;
vector<int> g[MAX_V],rg[MAX_V];
//void f_dfs(int s,vector<int> &st,vector<bool> &used,vector<vector<int> > g){
void f_dfs(int s,vector<int> &st,vector<bool> &used){
	used[s] = false;
for(int i=0;i<g[s].size();i++){
	if(used[g[s][i]]){
	//f_dfs(g[s][i],st,used,g);
	f_dfs(g[s][i],st,used);
	}
}
	st.push_back(s);
	return;
}	
//void s_dfs(int s,int num,vector<int>&grup, vector<bool> &rused,vector<vector<int> > rg){
void s_dfs(int s,int num,vector<int> &grup,vector<bool> &rused){
	rused[s] = true;
	grup[s] = num;
	for(int i=0;i<rg[s].size();i++){
	//if(!rused[rg[s][i]])s_dfs(rg[s][i],num,grup,rused,rg);
	if(!rused[rg[s][i]])s_dfs(rg[s][i],num,grup,rused);
	}
	return ;
}
//void strong(int v,vector<int>&grup,vector<vector<int> > g,vector<vector<int> >rg){
void strong(int v,vector<int> &grup){
 vector<int> st;
//vector<bool> used(v,true),rused(v,true);
vector<bool> used(v,true);
//for(int i=0;i<v;i++)if(used[i])f_dfs(i,st,used,g);
for(int i=0;i<v;i++)if(used[i])f_dfs(i,st,used);
int num = 1;

	for(int i=st.size()-1;i>=0;i--){
	int now = st[i];
	if(!used[now]){
	//s_dfs(now,num,grup,used,rg);
	s_dfs(now,num,grup,used);
	num++;
	}
	}
	return;
}
int main(){
int v,e;
cin>>v>>e;
//vector<vector<int> >  g(v),rg(v);
int s,t;
 rep(i,e){
	cin>>s>>t;
	g[s].push_back(t);
	rg[t].push_back(s);
 }
// stack<int> st;
vector<int> grup(v,0);
//vector<bool> used(v,true),rused(v,true);
//	f_dfs(0,st,used,g);
	/*cout<<"number of size"<<st.size()<<endl;
	while(!st.empty()){
	cout<<st.top()<<endl;
	st.pop();
	}*/
	//int num =1;
	/*while(!st.empty()){
	int now = st.top();
	st.pop();
	if(rused[now]){
	s_dfs(now,num,grup,rused,rg);
	num++;
	}
	}*/
//strong(v,grup,g,rg);
strong(v,grup);
int q;
cin>>q;

rep(i,q){
	int b,e;
cin>>b>>e;
if(grup[b]==grup[e]){
cout<<1<<endl;
}else{
cout<<0<<endl;
}

}
}

