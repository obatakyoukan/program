#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf = 1e18;

vector<mp> knapsack_table(vector<mp> &a){ // [s,t)
    int n = a.size();
    vector<mp> res( (1<<n) , mp(inf,inf)  );
    res[0] =  mp(0,0) ;
    for(int i=0;i< (1<<n) ; i++){
	for(int j=0;j<n;j++){
		if( (i>>j) & 1 ) continue;
		res[i|(1<<j)] =  min(res[ i | (1<<j) ] , mp(res[i].first +a[j].first , res[i].second + a[j].second  ) ) ;
	}
    }
    return res;
}

int main(){
    ll n,w;
    cin>>n>>w;
    vector<mp> a(n),b,c;//(w,v)
    for(int i=0;i<n;i++) cin>>a[i].second>>a[i].first;
    for(int i=0; i < n/2;i++) b.push_back( a[i] );
    for(int i=n/2;i < n;i++) c.push_back(a[i] );
    vector<mp> resb = knapsack_table(b);
    vector<mp> resc = knapsack_table(c);
    sort(resb.begin(),resb.end());
    sort(resc.begin(),resc.end());
    ll ans = 0;
    for(int i=1;i < resc.size();i++) resc[i].second = max( resc[i].second , resc[i-1].second ); // V maxの値に変える
    for(int i=0; i < resb.size() ;i++){
	ll W = resb[i].first;
	if( W > w ) break;
	ll V = resb[i].second;
	auto it = upper_bound(resc.begin(),resc.end(), mp(w-W, inf )  );
	int t = it-resc.begin();
	if(t==0) continue;
	if( W + resc[t-1].first > w) continue;
	ans = max( ans , V + resc[t-1].second ) ;
    }
    cout<<ans<<endl;

    return 0;
}

