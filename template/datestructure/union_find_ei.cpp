#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;

struct UnionFind {
  vector< int > data;
 
  UnionFind(int sz) {
    data.assign(sz, -1);
  }
 
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return (false);
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }
 
  int find(int k) {
    if(data[k] < 0) return (k);
    return (data[k] = find(data[k]));
  }
 
  int size(int k) {
    return (-data[find(k)]);
  }
};


int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  UnionFind uf(N);
  while(Q--) {
    int t, x, y;
    scanf("%d %d %d", &t, &x, &y);
    if(t == 0) uf.unite(x, y);
    else printf("%d\n", uf.find(x) == uf.find(y));
  }
}
