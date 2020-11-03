#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> mypair;




int main(){
int v,e;
cin>>v>>e;
vector<vector<mypair> >  g(v);
for(int i=0;i<e;i++){
int s,t,d;
cin>>s>>t>>d;
g[s].push_back(mypair(t,d));
}
/*for(int i=0;i<v;i++){
	for(int j=0;j<g[i].size();j++){
	cout<<g[i][j].first<<' ';
	}
	cout<<endl;
}*/
vector<vector<int> > dp((1<<v),vector<int> (v,(int)1e8));
dp[0][0]=0;
for(int i=0;i<(1<<v);i++){
	for(int j=0;j<v;j++){
	//	if(!((1<<j)&i)){
		if(dp[i][j]!=(int)1e8){	

			for(int k=0;k<g[j].size();k++){
				if(!(i&(1<<g[j][k].first))){
					int tmp=i|(1<<g[j][k].first);
					dp[tmp][g[j][k].first] = min(dp[tmp][g[j][k].first],dp[i][j]+g[j][k].second);
				}
			}
		}

	//	}
	}
}
int ans = dp[(1<<v)-1][0];
cout<< (ans==1e8 ? -1:ans)<<endl;
return 0;

}

