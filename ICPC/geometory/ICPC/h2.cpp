#include <bits/stdc++.h>
 
using namespace std;
 
using int64 = long long;
const int mod = 1e9 + 7;
 
int main() {
  int N, K, X[3000], Y[3000];
  cin >> N >> K;
  for(int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
  }
  for(int i = 0; i < N; i++) {
    map< pair< int, int >, int > mp;
    for(int j = 0; j < N; j++) {
      if(i == j)continue;
      auto x = X[i] - X[j];
      auto y = Y[i] - Y[j];
      if(x == 0) y = 1;
      if(y == 0) x = 1;
      if(x * y != 0) {
        if(x < 0) {
          x *= -1;
          y *= -1;
        }
        auto z = __gcd(x, y);
        x /= z;
        y /= z;
      }
      if(++mp[{x, y}] >= K - 1) {
        cout << 1 << endl;
        return 0;
      }
    }
  }
  cout << 0 << endl;
}
