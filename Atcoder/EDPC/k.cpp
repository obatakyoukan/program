#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;


int main(){
    int n,k;
    cin>>n>>k;
    vector<int> a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    vector<bool> dp(k+1,false);
    for(int i=0;i<=k;i++){
	for(int j=0;j<n;j++){
	    if( a[j]<=i ) dp[i] = dp[i] | ( !dp[i-a[j]] );
	}
    }
    if(dp[k])cout<<"First"<<endl;
    else cout<<"Second"<<endl;

    return 0;
}

