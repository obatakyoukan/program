// 基本テンプレート
#define _GLIBCXX_DEBUG // for STL debug
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
#include <cfloat>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <fstream>
#include <functional>
#include <bitset>
using namespace std;
 
#define rep(i,a,n) for(int (i)=(a); (i)<(n); (i)++)
#define repq(i,a,n) for(int (i)=(a); (i)<=(n); (i)++)
#define repr(i,a,n) for(int (i)=(a); (i)>=(n); (i)--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define int long long int
 
template<typename T> void chmax(T &a, T b) {a = max(a, b);}
template<typename T> void chmin(T &a, T b) {a = min(a, b);}
template<typename T> void chadd(T &a, T b) {a = a + b;}
 
typedef pair<int, int> pii;
typedef long long ll;
 
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
const ll INF = 1001001001001001LL;
const ll MOD = 1000000007LL;

// Ford-Fulkerson 法による 最大流 O( F |E| )
// Bellman-Ford 法による 最小費用流 O( F |V| |E| )
// Verified: AOJ GRL_6_A (Maximum Flow)

// 行き先と容量と逆辺のインデックスを記録する構造体
// 通常のグラフの辺の構造体と異なるため注意

// 最小費用流はもう少し速くできるので、改良しましょう
// → ダイクストラが使えるようにポテンシャルを導入しよう

template <typename Type>
struct Edge {
    int to; Type cap, cost; int rev;
    Edge(int t, Type c, int r) : to(t), cap(c), rev(r) {}
    Edge(int t, Type ca, Type co, int r) : to(t), cap(ca), cost(co), rev(r) {}
};

template <typename Type>
using Graph = vector< vector< Edge<Type> > >;

template <typename Type>
struct Flow {
    vector< vector< Edge<Type> > > G;
    const Type MAXC = 1 << 30;
    int n;
    vector<bool> used;
    vector<int> prevv, preve, dist;
    Flow(int _n) : G(_n), n(_n), used(_n, false), 
        prevv(_n), preve(_n), dist(_n, MAXC) {}

    // G[e.to][e.rev] で逆辺を操作できる
    void add_edge(int from, int to, Type cap) {
        G[from].push_back(Edge<Type>(to, cap, G[to].size()));
        G[to].push_back(Edge<Type>(from, 0, G[from].size() - 1));
    }
    void add_edge(int from, int to, Type cap, Type cost) {
        G[from].push_back(Edge<Type>(to, cap, cost, G[to].size()));
        G[to].push_back(Edge<Type>(from, 0, -cost, G[from].size() - 1));
    }

    Type dfs(int v, int t, Type f) {
        if(v == t) return f;
        used[v] = true;
        for(int i=0; i < G[v].size(); i++) {
            Edge<Type> &e = G[v][i];
            if(!used[e.to] && e.cap > 0) {
                Type d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    Type max_flow(int s, int t) {
        Type flow = 0;
        while(1) {
            fill(used.begin(), used.end(), false);
            Type f = dfs(s, t, INF);
            if(f == 0) return flow;
            flow += f;
        }
    }

    Type mincost_flow(int s, int t, Type f) {
        Type res = 0;
        Type ma = MAXC;
        while(f > 0) {
            fill(dist.begin(), dist.end(), ma);
            dist[s] = 0;
            bool update = true;
            while(update) {
                update = false;
                for(int v = 0; v < n; v++) {
                    if(dist[v] == ma) continue;
                    for(int i=0; i<G[v].size(); i++) {
                        Edge<Type> &e = G[v][i];
                        if(e.cap>0 && dist[e.to] > dist[v] + e.cost) {
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            update = true;
                        }
                    }
                }
            }

            if(dist[t] == ma) return -1;
            Type d = f;
            for(int v = t; v != s; v = prevv[v]) {
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * dist[t];
            for(int v = t; v != s; v = prevv[v]) {
                Edge<Type> &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }

    // ポテンシャルの導入により、ダイクストラ法で最小費用流を解く
    // [仮定している条件]
    //     1. グラフに負の閉路が存在しない (流量の 0 初期化のため)
    //        もし存在するならベルマンフォードで負の閉路を見つけ
    //        そこに流せるだけ流してスタート
    //     2. グラフに負の辺が存在しない (pot_0 の計算可能性)
    //        もし存在する場合は最初のみベルマンフォードを使う必要あり
    Type fast_mincost_flow(int s, int t, Type f) {
        Type res = 0, ma = MAXC;
        vector<Type> pot(n);
        while(f > 0) {
            using PT = pair<Type, int>;
            priority_queue< PT, vector<PT>, greater<PT> > que;
            fill(dist.begin(), dist.end(), ma);

            dist[s] = 0;
            que.push(make_pair(0, s));
            while(!que.empty()) {
                PT cur = que.top(); que.pop();
                int v = cur.second;
                if(dist[v] < cur.first) continue;
                for(size_t i=0; i<G[v].size(); i++) {
                    Edge<Type>& e = G[v][i];
                    if(e.cap > 0 and dist[e.to] > dist[v] + e.cost + pot[v] - pot[e.to]) {
                        dist[e.to] = dist[v] + e.cost + pot[v] - pot[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push(make_pair(dist[e.to], e.to));
                    }
                }
            }
            if(dist[t] == ma) {
                return -1;
            }
            for(int v=0; v<n; v++) pot[v] += dist[v];

            Type d = f;
            for(int v=t; v!=s; v=prevv[v]) {
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * pot[t];
            for(int v=t; v!=s; v=prevv[v]) {
                Edge<Type>& e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};

signed main() {
    int V, E, F; cin >> V >> E >> F;

    Flow<int> fl(V);
    for(int i=0; i<E; i++) {
        int u, v, c, d; cin >> u >> v >> c >> d;
        fl.add_edge(u, v, c, d);
    }

    cout << fl.fast_mincost_flow(0, V-1, F) << endl;
    return 0;
}

