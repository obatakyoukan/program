#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cmath>
#include <limits>
#include <climits>
#include <ctime>
#include <cassert>
using namespace std;

#define rep(i,a,n) for(int (i)=(a); (i)<(n); (i)++)
#define repq(i,a,n) for(int (i)=(a); (i)<=(n); (i)++)
#define repr(i,a,n) for(int (i)=(a); (i)>=(n); (i)--)
#define all(v) begin(v), end(v)
#define pb(a) push_back(a)
#define fr first
#define sc second
#define INF 2000000000

#define X real()
#define Y imag()
#define EPS (1e-10)
#define EQ(a,b) (abs((a) - (b)) < EPS)
#define EQV(a,b) ( EQ((a).X, (b).X) && EQ((a).Y, (b).Y) )
#define LE(n, m) ((n) < (m) + EPS)
#define LEQ(n, m) ((n) <= (m) + EPS)
#define GE(n, m) ((n) + EPS > (m))
#define GEQ(n, m) ((n) + EPS >= (m))

typedef vector<int> VI;
typedef vector<VI> MAT;
typedef pair<int, int> pii;
typedef long long ll;

typedef complex<double> P;
typedef pair<P, P> L;
typedef pair<P, double> C;

int dy[]={0, 0, 1, -1};
int dx[]={1, -1, 0, 0};
int const MOD = 1000000007;

namespace std {
    bool operator<(const P& a, const P& b) {
        return a.X != b.X ? a.X < b.X : a.Y < b.Y;
    }
}

// ?§?????????¨????????¨???????????????????¨???????????§???????
template <typename T>
struct Edge {
    int from, to;
    T cost;
    Edge(int s, T d) : to(s), cost(d) {}
    Edge(int f, int s, T d) : from(f), to(s), cost(d) {}

    bool operator<(const Edge &e) const {
        return cost < e.cost;
    }
    bool operator>(const Edge &e) const {
        return cost > e.cost;
    }
};

template <typename T>
vector<T> dijkstra(vector< vector< Edge<T> > > &G, int s) {
    int V = G.size();
    vector<T> d(V); fill(d.begin(), d.end(), INF);
    priority_queue<pii, vector<pii>, greater<pii> > que;
    d[s] = 0;
    que.push(pii(0,s));

    while(!que.empty()) {
        pii p = que.top(); que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;
        for(int i=0; i<G[v].size(); i++) {
            Edge<T> e = G[v][i];
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(pii(d[e.to], e.to));
            }
        }
    }
    return d;
}

template <typename T>
vector<T> treeHeight(vector< vector< Edge<T> > > &G) {
    int n = G.size();
    vector<T> v1, v2, v3, ret(n);
    int p1, p2;
    v1 = dijkstra<T>(G, 0);
    p1 = max_element(v1.begin(), v1.end()) - v1.begin();

    v2 = dijkstra<T>(G, p1);
    p2 = max_element(v2.begin(), v2.end()) - v2.begin();

    v3 = dijkstra<T>(G, p2);
    for(int i=0; i<n; i++) ret[i] = max(v2[i], v3[i]);
    return ret;
}

signed main() {
    int n; cin >> n;
    vector< vector< Edge<int> > > G(n);
    int s, t, w;
    rep(i,0,n-1) {
        cin >> s >> t >> w;
        G[s].pb(Edge<int>(t,w));
        G[t].pb(Edge<int>(s,w));
    }

    vector<int> ans = treeHeight<int> (G);
    rep(i,0,ans.size()) cout << ans[i] << endl;
    return 0;
}
