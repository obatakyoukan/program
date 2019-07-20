#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,string> mp;
ll inf =  1e9;

int main(){
    string s,t;
    cin>>s>>t;
    int n1 = s.size(),n2 = t.size();
    vector<vector<int> > dp(n1+1 , vector<int>(n2+1, 0) );
    for(int i=1;i<=n1;i++){
	for(int j=1;j<=n2;j++){
	    if(s[i-1] == t[j-1] ){
		dp[i][j] = dp[i-1][j-1]+1; 
	    }else{
		dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
	    }
	}
    }
   // cout<<dp[n1][n2]<<endl;
   string ans="";
   int x = n1,y = n2;
   while( x>0 && y>0){
       if( dp[x][y] == dp[x-1][y]){
	   x--;
       }else if(dp[x][y] == dp[x][y-1]){
	   y--;
       }else{
	   x--,y--;
	   ans += s[x];
       }
   }
   reverse(ans.begin(),ans.end());
   cout<<ans<<endl;
    return 0;
}

