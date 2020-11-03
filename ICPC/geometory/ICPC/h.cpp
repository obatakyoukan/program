#include<bits/stdc++.h>
using namespace std;
typedef long ld;
typedef pair<ld,ld> mp;
#define inf 1e9
typedef pair<ld,mp> mmp;
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}

int main(){
	int n,k;
	cin>>n>>k;
	vector<mp> a(n);
	for(int i=0;i<n;i++){
		cin>>a[i].first>>a[i].second;
	}
	bool f = false;
	
	for(int i=0;i<n;i++){
		map<mp,int> st;
		if(!f) for(int j=i+1;j<n;j++){
		    	if(i==j)continue;
		    	ld dx = a[i].first-a[j].first;
			ld dy = a[i].second-a[j].second ;
			int d = 1;
			if(dx==0)dy=1;
			else if(dy==0)dx=1;
			else{
				if(dx<0){
					dx*=-1;
					dy*=-1;
				}	
				 d = gcd(abs((int)dx),abs((int)dy ));
				 dx/=d;
				 dy/=d;
			}
			if(++st[{dx,dy}]>=k-1){
				f= true;
				break;
			}
			
		}
	}
	if(f)cout<<1<<endl;
	else cout<<0<<endl;
	return 0;
}

