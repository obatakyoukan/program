#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define inf 1e9
typedef pair<int,int> mypair;
void dai(vector<vector<mypair> > g,vector<mypair> &d,int s,int n){
	rep(i,n) d.push_back(mypair(inf,i));
	d[s] = mypair(0,s);
	priority_queue<mypair,vector<mypair>,greater<mypair> > q;
	q.push(mypair(0,s));
	while(!q.empty()){
	mypair now =q.top();
	//cout<<now.first<<' '<<now.second<<endl;
	q.pop();
		rep(i,g[now.second].size()){
			int next = g[now.second][i].second;
			int nextcost = g[now.second][i].first;
			if(d[next].first>nextcost+now.first){
				d[next].first  = nextcost+now.first;
				q.push(d[next]);
			}
		}
	}
	return;
}

int main(){
	int n;
	cin>>n;
vector<vector<mypair> > g(n);
for(int i=0;i<n-1;i++){
int s,t,w;
cin>>s>>t>>w;
g[s].push_back(mypair(w,t));
g[t].push_back(mypair(w,s));
}
//cout<<"ok"<<endl;
vector<mypair> d,d2;
dai(g,d,0,n);
sort(d.begin(),d.end());
int ma = d[n-1].second;
//cout<<ma<<' '<<d[ma].first<<"ma"<<endl;
dai(g,d2,ma,n);
sort(d2.begin(),d2.end());
cout<<d2[n-1].first<<endl;



}

