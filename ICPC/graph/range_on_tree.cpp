// 基本テンプレート
 
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
using namespace std;
 
#define rep(i,a,n) for(int (i)=(a); (i)<(n); (i)++)
#define repq(i,a,n) for(int (i)=(a); (i)<=(n); (i)++)
#define repr(i,a,n) for(int (i)=(a); (i)>=(n); (i)--)
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

// vector 版 (HL 分解に載せるときとかに使おう)
template<typename T>
struct lazysegtree {
    // ノード、単位元
    T I_upd, I_qry;
    vector<T> node, lazy;
    vector<bool> need_upd;
    int SIZE;

    // オペレーション (update, query の 2 つが必要？)
    // update function は範囲を指定する形にしよう
    // upd_f(X, Y, l, r) -> 範囲が [l, r) であるようなノード X に Y を反映！
    // lazy について update するときは範囲を 1 にしないとバグります
    T (*upd_f)(T, T, int, int), (*qry_f)(T, T);

    // 演算子と単位元をセットし、全ての node と lazy を単位元で初期化
    lazysegtree(int seg_size, T (*op1)(T, T, int, int), T (*op2)(T, T), T X_upd, T X_qry) {
        upd_f = op1;
        qry_f = op2;
        I_upd = X_upd, I_qry = X_qry;
        SIZE = 1; while(SIZE < seg_size) SIZE *= 2;
        node     = vector<T> (2*SIZE, I_qry);
        lazy     = vector<T> (2*SIZE, I_upd);
        need_upd = vector<bool>(2*SIZE, false);
    }

    // 配列 vec の値で初期化
    void init(vector<T> vec) {
        int N = (int)vec.size();
        for(int i=0; i<N; i++) {
            node[SIZE-1+i] = vec[i];
        }
        for(int i=SIZE-2; i>=0; i--) {
            node[i] = qry_f(node[2*i+1], node[2*i+2]);
        }
    }

    void lazy_eval(int k, int l, int r) {
        if(!need_upd[k]) return;
        node[k] = upd_f(node[k], lazy[k], l, r);
        if(r - l > 1) {
            lazy[2*k+1] = upd_f(lazy[2*k+1], lazy[k], 0, 1);
            lazy[2*k+2] = upd_f(lazy[2*k+2], lazy[k], 0, 1);
            need_upd[2*k+1] = need_upd[2*k+2] = true;
        }
        lazy[k] = I_upd;
        need_upd[k] = false;
    }

    // 半開区間 [a, b) に対して値 val を反映させる
    // (upd_f を用いて処理)
    void update(int a, int b, T val, int l=0, int r=-1, int k=0) {
        if(r < 0) r = SIZE;
        lazy_eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = upd_f(lazy[k], val, 0, 1);
            need_upd[k] = true;
            lazy_eval(k, l, r);
        }
        else {
            int mid = (l + r) / 2;
            update(a, b, val, l, mid, 2*k+1);
            update(a, b, val, mid, r, 2*k+2);
            node[k] = qry_f(node[2*k+1], node[2*k+2]);
        }
    }

    // 半開区間 [a, b) に対してクエリを投げる
    // (qry_f を用いて処理)
    T query(int a, int b, int l=0, int r=-1, int k=0) {
        if(r < 0) r = SIZE;
        lazy_eval(k, l, r);
        if(b <= l || r <= a) return I_qry;
        if(a <= l && r <= b) return node[k];
        int mid = (l + r) / 2;
        T vl = query(a, b, l, mid, 2*k+1);
        T vr = query(a, b, mid, r, 2*k+2);
        return qry_f(vl, vr);
    }
};

// HL 分解
// ある頂点 v の子たち c_i について、それを根とする部分木の頂点数が
// 最大のものの 1 つを c_h とおく。このとき、辺 (v, c_h) は "heavy" な辺であるという。
// それ以外の辺は "light" な辺であるという。

// すべての辺を "heavy" と "light" に分類すると、木は "heavy" からなるパス
// (下のコードだと chain) に分解 ("heavy" でつながっている頂点をひとつにまとめる) できる。
// これを HL 分解という。

// chain を縮約したあとの木の高さは O(log N) である。
// これは、"heavy" な辺の定義より、頂点 v と "light" な辺で結ばれている v の子それぞれに対して、
// 部分木の大きさが subsize(v) / 2 以下となっていることから導ける。
// "light" な辺を通るたびに部分木のサイズが半分以下になるため、深さは O(log N) となる。

// 移動元と行先と辺のコストを記録する構造体
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
using Graph = vector< vector< Edge<T> > >;

template <typename Type>
struct HLD {
    int N;
    const Graph<int> G;
    // ・元の木について
    // 根からの深さ、自分の親、自分を根にしたときの部分木のサイズ
    // および、その頂点から出る "heavy" な辺
    vector<int> depth, parent, subsize, heavy;
    // ・chain について
    // chain の先頭要素、末尾要素、その頂点の 1 つ次・前の要素、chain 内でのインデックス
    vector<int> head, last, prev, next, chain, idx;
    // chain の情報 (同じ vector 内にある要素どうしは同じ chain に属する)
    vector< vector<int> > chains;
    // 各 chain に載せる遅延評価セグ木 (抽象)
    vector< lazysegtree<Type> > segs;

    HLD(const Graph<int> &H, int r=-1) :
        N(H.size()), G(H), depth(N, -1), parent(N, 0), subsize(N, 0), heavy(N, -1),
        head(N), last(N), prev(N, -1), next(N, -1), chain(N, -1), idx(N, 0)
    {
        if(r != -1) decompose(r);
    }

    // root を根として分解
    void decompose(const int root) {
        stack<int> st; st.push(root);
        parent[root] = -1;
        depth[root] = 0;        

        while(st.size()) {
            int cur_v = st.top(); st.pop();
            // その頂点を初めて訪れた
            if(cur_v >= 0) {
                st.push(~cur_v);
                for(auto e : G[cur_v]) {
                    // 親の方向でなければ値を更新
                    if(depth[e.to] != -1) continue;
                    depth[e.to] = depth[cur_v] + 1;
                    parent[e.to] = cur_v;
                    st.push(e.to);
                }
            }
            // 帰りがけ
            else {
                int ma = 0;
                cur_v = ~cur_v;
                subsize[cur_v] = 1;
                for(auto e : G[cur_v]) {
                    if(parent[cur_v] == e.to) continue;
                    subsize[cur_v] += subsize[e.to];
                    if(ma < subsize[e.to]) {
                        // cur_v と部分木のサイズが最大の子を結ぶ
                        // (これが "heavy" の辺)
                        ma = subsize[e.to];
                        heavy[cur_v] = e.to;
                    }
                }
            }
        }

        st.push(root);
        while(st.size()) {
            int cur_v = st.top(); st.pop();
            for(auto e : G[cur_v]) {
                if(parent[cur_v] != e.to) st.push(e.to);
            }

            // すでにその頂点について構築済みなら、何もしない
            // (chain の先頭の頂点でない)
            if(chain[cur_v] != -1) continue;
            chains.push_back(vector<int>());
            vector<int> &path = chains.back();

            // cur_v を始点として、heavy な辺をたどりながら下がる
            for(int v=cur_v; v!=-1; v=heavy[v]) {
                path.push_back(v);
            }

            for(size_t i=0; i<path.size(); i++) {
                // path (chain) の i 番目の頂点 v に関する情報
                int v = path[i];
                head[v] = path.front(), last[v] = path.back();
                prev[v] = (i != 0 ? path[i-1] : -1);
                next[v] = (i+1 != path.size() ? path[i+1] : -1);
                chain[v] = (int)chains.size() - 1;
                idx[v] = i;
            }
        }
    }

    // chain の個数分だけ segtree を作る
    void buildSegtree(Type (*op1)(Type, Type, int, int), Type (*op2)(Type, Type), Type X_upd, Type X_qry) {
        segs.clear();
        for(size_t i=0; i<chains.size(); i++) {
            segs.push_back(lazysegtree<Type>(chains[i].size(), op1, op2, X_upd, X_qry));
        }
    }

    // 頂点 v について、どの chain に属するか、
    // またその chain の中でのインデックスは何かを pair で返す
    pair<int, int> get_index(int v) {
        return make_pair(chain[v], idx[v]);
    }

    void debug_path() {
        for(size_t i=0; i<chains.size(); i++) {
            fprintf(stderr, "path:");
            for(size_t k=0; k<chains[i].size(); k++) {
                fprintf(stderr, " %lld", chains[i][k]);
            }
            fprintf(stderr, "\n");
        }
    }

    // v が属する chain の先頭を返す (head[v] が根なら -1 を返す)
    int climb(int v) {
        return parent[ head[v] ];
    }

    // 頂点 u と v の最小共通祖先
    int lca(int u, int v) {
        // 同じ chain に属するまで登る
        while(chain[u] != chain[v]) {
            if(depth[head[u]] < depth[head[v]]) v = climb(v);
            else u = climb(u);
        }
        // 属する chain が同じになれば、浅いほうが LCA
        return depth[u] < depth[v] ? u : v;
    }

    // lca で分解されたあとのパスについて、クエリを処理
    void update_base(int u, int v, Type x, int f) {
        while(1) {
            // u の方が深い
            if(depth[u] < depth[v]) swap(u, v);

            // 属する chain が異なる → 先頭まで全部更新
            if(chain[u] != chain[v]) {
                int lhs = 0, rhs = idx[u] + 1;
                segs[ chain[u] ].update(lhs, rhs, x);
                u = climb(u);
            }
            // 同じ → v を含めるかどうかに気をつけながら更新
            else {
                int lhs = idx[v] + 1 - f, rhs = idx[u] + 1;
                segs[ chain[u] ].update(lhs, rhs, x);
                break;
            }
        }
    }

    // 頂点 u - v 間の「点」それぞれについて更新
    // f は anc を更新対象に含めるかどうか
    void upd_vertex(int u, int v, Type x) {
        int anc = lca(u, v);
        update_base(u, anc, x, 1);
        update_base(v, anc, x, 0);
    }

    // 頂点 u - v 間の「辺」それぞれについて更新
    void upd_edge(int u, int v, Type x) {
        int anc = lca(u, v);
        update_base(u, anc, x, 0);
        update_base(v, anc, x, 0);
    }

    // lca で分解されたあとのパスについて、クエリを処理
    Type query_base(int u, int v, Type X, Type (*op)(Type, Type), int f) {
        Type ret = X;
        
        while(1) {
            if(depth[u] < depth[v]) swap(u, v);

            // A (根に近い) op B (遠い) の順番 (B op A ではない)
            // u と v の chain が異なるならば、chain の端まで上って次へ
            if(chain[u] != chain[v]) {
                int lhs = 0, rhs = idx[u] + 1;
                ret = op(segs[ chain[u] ].query(lhs, rhs), ret);
                u = climb(u);
            }
            // lhs を含むか含まないか (f = 1 で含む)
            else {
                int lhs = idx[v] + 1 - f, rhs = idx[u] + 1;
                ret = op(segs[ chain[u] ].query(lhs, rhs), ret);
                break;
            }
        }
        return ret;
    }

    // 頂点 u - v 間の「点」に関するクエリ (単位元と関数も必要)
    Type qry_vertex(int u, int v, Type X, Type (*op)(Type, Type)) {
        int anc = lca(u, v);
        Type ret = X;
        ret = op(ret, query_base(anc, u, X, op, 1));
        ret = op(ret, query_base(anc, v, X, op, 0));
        return ret;
    }

    // 頂点 u - v 間の「辺」に関するクエリ
    Type qry_edge(int u, int v, Type X, Type (*op)(Type, Type)) {
        int anc = lca(u, v);
        Type ret = X;
        ret = op(ret, query_base(anc, u, X, op, 0));
        ret = op(ret, query_base(anc, v, X, op, 0));
        return ret;
    }
};

// [[つかいかた]]
// update 用と query 用の関数と単位元 (関数を噛ませても結果が変わらないもの) を用意して宣言する
// 下の例だと、update 用の関数が upd で、query 用の関数が fnd で、udpate の (作用素の) 単位元が 0、query の単位元が 0

// 範囲が [l, r) のノードの値 a に値 b を反映させる
ll upd(ll a, ll b, int l, int r) {return a + (r - l) * b;}
// ノードの値 a と b に対してどのような操作をするか？
ll fnd(ll a, ll b) {return a+b;}

int parent[100010];
 
signed main() {
    int N; cin >> N;

    Graph<int> G(N);
    for(int i=0; i<N; i++) {
        int K; cin >> K;
        for(int k=0; k<K; k++) {
            int ch; cin >> ch;
            parent[ch] = i;

            G[i].push_back(Edge<int>(ch, 1));
            G[ch].push_back(Edge<int>(i, 1));
        }
    }

    HLD<int> hl(G, 0);
    hl.buildSegtree(upd, fnd, 0, 0);

    int Q; cin >> Q;
    for(int i=0; i<Q; i++) {
        int query; cin >> query;
        if(query == 0) {
            int v, w; cin >> v >> w;
            hl.upd_edge(parent[v], v, w);
        }
        if(query == 1) {
            int u; cin >> u;
            cout << hl.qry_edge(0, u, 0, fnd) << endl;
        }
    }
    return 0;
}
