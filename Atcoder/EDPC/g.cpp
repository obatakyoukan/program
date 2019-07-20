#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

void dfs(vector<bool> &used,int s,vector<vector<int> > &g,vector<int> &res){
    used[s] = false;
    for(int i=0;i<g[s].size();i++){
	if(used[g[s][i]])dfs(used,g[s][i],g,res);
    }
    res.push_back(s);
    return ;
}
vector<int> tsort(vector<vector<int> > &g){
    int n = g.size();
    vector<bool> used(n,true);
    vector<int> res;
    for(int i=0;i<n;i++)if(used[i])dfs(used,i,g,res);
    return res;
}



int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int> > g(n);
    vector<int> dp(n,0);
    for(int i=0;i<m;i++){
	int x,y;
	cin>>x>>y;
	x--,y--;
	g[x].push_back(y);
    }
    vector<int> res = tsort(g);
 
    for(int i=0;i<n;i++){
	int now = res[i];
	for(int j=0;j<g[now].size();j++){
	    dp[now] = max(dp[now],dp[g[now][j]] + 1);
	}
    }
    int ans = 0;
    for(int i=0;i<n;i++)ans = max(ans,dp[i]);
    cout<<ans<<endl;
  //  for(int i=0;i<n;i++)cout<<' '<<dp[res[i]]<<' '<<res[i]<<endl;

    return 0;
}

