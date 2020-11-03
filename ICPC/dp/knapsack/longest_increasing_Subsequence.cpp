#include<bits/stdc++.h>
using namespace std;
#define inf 1000000001
vector<int> lis(vector<int> a){
	int n = a.size();
	vector<int> tmp(n,inf);
	vector<int> it(n);
	for(int i=0;i<n;i++){
	auto k = lower_bound(tmp.begin(),tmp.end(),a[i])-tmp.begin();
	it[i]= k;		
	tmp[k]= a[i];

	}
	int m = *max_element(it.begin(),it.end());
	vector<int> res(m+1);
	for(int i=n-1;i>=0;i--){
	if(it[i]==m){
		res[m] = a[i];
		m--;
		}
	}
	return res;
}

int main(){
int n;
cin>>n;
vector<int> a(n);
for(int i=0;i<n;i++){ cin>>a[i];}
vector<int > ans = lis(a);
cout<< ans.size()<<endl;
	return 0;
}

