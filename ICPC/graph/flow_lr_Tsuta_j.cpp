#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cassert>
using namespace std;
const int INF = 1 << 28;

struct Edge {
  int to, cap, cost, rev;
  Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
  Edge(int t, int ca, int co, int r) : to(t), cap(ca), cost(co), rev(r) {}
};

using Graph = vector< vector<Edge> >;

struct Dinic {
  int N;
  Graph G;
  vector<int> level, iter;
  Dinic() {}
  Dinic(int n) : N(n) {
    G.resize(N);
    level.resize(N);
    iter.resize(N);
  }
  void add_edge(int from, int to, int cost) {
    G[from].push_back(Edge(to, cost, G[to  ].size()   ));
    G[to  ].push_back(Edge(from, 0, G[from].size() - 1));
  }
  void bfs(int s) {
    fill(level.begin(), level.end(), -1);
    queue<int> que; que.push(s);
    level[s] = 0;
    while(que.size()) {
      int temp = que.front(); que.pop();
      for(size_t i=0; i<G[temp].size(); i++) {
        Edge &e = G[temp][i];
        if(e.cap > 0 and level[e.to] < 0) {
          level[e.to] = level[temp] + 1;
          que.push(e.to);
        }
      }
    }
  }
  int dfs(int v, int t, int f) {
    if(v == t) return f;
    for(int &i = iter[v]; i<(int)G[v].size(); i++) {
      Edge &e = G[v][i];
      if(e.cap > 0 and level[v] < level[e.to]) {
        int d = dfs(e.to, t, min(f, e.cap));
        if(d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }
  int max_flow(int s, int t) {
    int flow = 0, f;
    while(1) {
      bfs(s);
      if(level[t] < 0) return flow;
      fill(iter.begin(), iter.end(), 0);
      while( (f = dfs(s, t, INF)) > 0 ) flow += f;
    }
  }
};

struct Dinic_lr {
  Dinic fl;
  int S, T;
  int sum_lb;
  Dinic_lr() {}
  Dinic_lr(int N) : fl(N+2), S(N), T(N+1), sum_lb(0) {}

  void add_edge(int u, int v, int lb, int ub) {
    // assert(0 <= lb and lb <= ub);
    if(u == v or ub == 0) return;
    fl.add_edge(u, v, ub - lb);
    fl.add_edge(S, v, lb);
    fl.add_edge(u, T, lb);
    sum_lb += lb;
  }

  int max_flow(int s, int t) {
    int a = fl.max_flow(S, T);
    int b = fl.max_flow(s, T);
    int c = fl.max_flow(S, t);
    int d = fl.max_flow(s, t);

    return (a + c == sum_lb and a + b == sum_lb) ? b + d : -1;
  }
};

void ans_update(pair<int, int> &A, pair<int, int> B) {
  int saba = A.second - A.first;
  int sabb = B.second - B.first;
  if(saba > sabb) {
    A = B;
  }
  else if(saba == sabb) {
    if(A.first < B.first) {
      A = B;
    }
  }
}

int main() {
  int N, M; //  cin >> N >> M;
  while(cin >> N >> M, N || M) {
    vector<int> u(M), v(M);
    for(int i=0; i<M; i++) {
      cin >> u[i] >> v[i];
      u[i]--; v[i]--;
    }

    pair<int, int> ans(0, INF);
    for(int R=N; R>=1; R--) {
      int ub = R+1, lb = -1;
      while(ub - lb > 1) {
        int mid = (ub + lb) / 2;

        Dinic_lr fl(N + M + 2);
        // lb, ub
        int source = N + M, sink = source + 1;
        for(int i=0; i<M; i++) {
          fl.add_edge(source, i, 0, 1);
          fl.add_edge(i, M + u[i], 0, 1);
          fl.add_edge(i, M + v[i], 0, 1);
        }
        for(int i=0; i<N; i++) {
          fl.add_edge(M + i, sink, mid, R);
        }

        int flow = fl.max_flow(source, sink);
        if(flow == M) {
          lb = mid;
        }
        else {
          ub = mid;
        }
      }

      pair<int, int> cand(lb, R);
      if(lb < 0) continue;
      ans_update(ans, cand);
    }

    printf("%d %d\n", ans.first, ans.second);
  }
  return 0;
}
