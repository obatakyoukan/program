#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int A,B;
    cin>>A>>B;
    vector<int> a(A),b(B);
    for(int i=0;i<A;i++)cin>>a[i];
    for(int i=0;i<B;i++)cin>>b[i];
    vector<vector<int> > dp(A+1,vector<int>(B+1,-inf) );
    dp[A][B] = 0;
    for(int i=A;i>=0;i--){
	for(int j=B;j>=0;j--){
	    if(i==A&&j==B)continue;
	    if( (i+j)%2 == 0){//先手
		if(i==A)dp[A][j] = dp[A][j+1] + b[j];
		else if(j==B) dp[i][B] = dp[i+1][B] + a[i];
		else dp[i][j] = max(dp[i+1][j] + a[i],dp[i][j+1] + b[j]);
	    }else{//後手
		if(i==A) dp[A][j] = dp[A][j+1];
		else if(j==B) dp[i][B] = dp[i+1][B];
		else dp[i][j] = min(dp[i+1][j],dp[i][j+1]);
	    }
	}
    }

    cout<<dp[0][0]<<endl;

    return 0;
}

