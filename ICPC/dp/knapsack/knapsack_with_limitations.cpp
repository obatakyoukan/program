#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
int N,W;
vector<int> dp,v,w,m;
int solve(){//O(NWlogm) O(NW)は蟻本P302
    for(int i=0;i<N;i++){
	int num = m[i];
	for(int j=1;num > 0; j<<=1 ){
	    int mul = min(j,num);//最後を上手くやる
	    for(int j=W; j>=w[i]*mul;j--){
		dp[j] = max(dp[j],dp[j-w[i]*mul] + v[i]*mul);
	    }
	    num-=mul;
	}
    }
    return dp[W];
}

int main(){
    cin>>N>>W;
    dp = vector<int>(W+1,0);
    v = vector<int>(N);
    w = vector<int>(N);
    m = vector<int>(N);
    for(int i=0;i<N;i++)cin>>v[i]>>w[i]>>m[i];
    cout<<solve()<<endl;
    return 0;
}

