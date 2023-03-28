#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define fast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define _ <<' '<<
#define ALL(v) v.begin(),v.end()
#define ft first
#define sd second
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

const int MAXN = 200;
const int INF = 1e9;

struct MaxFlow { // 0-base
  struct edge {
    int to, cap, flow, rev;
  };
  vector<edge> G[MAXN];
  int s, t, dis[MAXN], cur[MAXN], n;
  int dfs(int u, int cap) {
    if (u == t or !cap) return cap;
    for (int &i = cur[u]; i < (int)G[u].size(); i++) {
      edge &e = G[u][i];
      if (dis[e.to] == dis[u]+1 and e.flow != e.cap) {
        int df = dfs(e.to, min(e.cap - e.flow, cap));
        if (df) {
          e.flow += df;
          G[e.to][e.rev].flow -= df;
          return df;
        }
      }
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs() {
    memset(dis, -1, sizeof(dis));
    queue<int> q;
    q.push(s), dis[s] = 0;
    while (q.size()) {
      int tmp = q.front(); q.pop();
      for (auto &u : G[tmp])
        if (dis[u.to] == -1 and u.flow != u.cap) {
          q.push(u.to);
          dis[u.to] = dis[tmp] + 1;
        }
    }
    return dis[t] != -1;
  }
  int maxflow(int _s, int _t) {
    s = _s, t = _t;
    int flow = 0, df;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      while (df = dfs(s, INF)) flow += df;
    }
    return flow;
  }
  void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i) G[i].clear();
  }
  void reset() {
    for (int i = 0; i < n; ++i)
      for (auto &j : G[i]) j.flow = 0;
  }
  void add_edge(int u, int v, int cap) {
    G[u].emplace_back(edge{ v, cap, 0, (int)G[v].size() });
    G[v].emplace_back(edge{ u, 0, 0, (int)G[u].size()-1 });
  }
};

signed main(){
    fast;
    int n, m;
    cin >> n >> m;

    MaxFlow dinic;
    dinic.init(n * 2 + 50);
    for (int i = 1; i <= n; ++i) {
        dinic.add_edge(i, i+n, 1);
    }

    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        dinic.add_edge(a+n, b, INF);
        dinic.add_edge(b+n, a, INF);
    }

    int ans = n-1;
    for (int i = 2; i <= n; ++i) {  
        dinic.reset();
        int flow = dinic.maxflow(i + n, j);
        ans = min(ans, flow);
    }
    cout << ans << '\n';
}