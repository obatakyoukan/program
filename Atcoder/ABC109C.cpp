#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

ll gcd(ll a,ll b){
    if(b==0)return a;
    return gcd( b, a%b);
}

int main(){
    ll n,x;
    cin>>n>>x;
    vector<ll> a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)a[i] = abs(a[i]-x);
    ll res = a[0];
    for(int i=1;i<n;i++) res = gcd(res,a[i]);
    cout<<res<<endl;
    return 0;
}

