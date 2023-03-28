#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define fast
#else
#define fast cin.tie(0)->sync_with_stdio(0)
#define endl '\n'
#define cerr if(1);else cerr
#endif
#define _ <<' '<<
#define ALL(v) v.begin(),v.end()
#define ft first
#define sd second

using ll = long long;
using LL = ll; // __int128;
using ld = long double;
using pii = pair<int,int>;
using pil = pair<int,ll>;

constexpr ll MOD1 = 1e9+7;
constexpr ll MOD2 = 998244353;
struct HASH {
    ll a = 0, b = 0;
    void operator+=(const HASH h) {
        a += h.a; if (a >= MOD1) a -= MOD1;
        b += h.b; if (b >= MOD2) b -= MOD2;
    }
    HASH(ll _a, ll _b){a = _a, b = _b;}
};
HASH operator*(HASH x, HASH y) {
    return HASH(
        ll( LL(1) * x.a * y.a % MOD1 ),
        ll( LL(1) * x.b * y.b % MOD2 )
    );
}
bool operator==(HASH x, HASH y) {
    return x.a == y.a and x.b == y.b;
}

void calc(int n, int s, const vector<vector<pil>>& G, vector<ll>& v) {
    v.assign(n, 3e18);
    priority_queue<pair<ll,int>> pq{};
    auto add = [&](int x, ll d) {
        if (d < v[x]) {
            v[x] = d;
            pq.emplace(-d, x);
        }
    };
    add(s, 0);
    while (!pq.empty()) {
        auto [d,x] = pq.top(); pq.pop();
        d *= -1;
        if (d != v[x]) continue;
        for(auto [y,w]: G[x]) {
            add(y, d+w);
        }
    }
}

void run(int n, int s, const vector<vector<pil>>& G, vector<HASH>& cnt) {
    cnt.assign(n, HASH(0,0));
    vector<int> in(n,0);
    for(int x = 0; x < n; x++)
        for(auto [y,w]: G[x])
            in[y]++;
    queue<int> que{};
    cnt[s] = { 1, 1 };
    for(int i = 0; i < n; i++)
        if (in[i] == 0)
            que.push(i);
    while (que.size()) {
        int x = que.front(); que.pop();
        for(auto [y,w]: G[x]) {
            cnt[y] += cnt[x];
            if (--in[y] == 0)
                que.push(y);
        }
    }
}

signed main() {
    fast;

    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,ll>> edge(m);
    vector<vector<pil>> G(n), rG(n);
    for(auto &[u,v,w]: edge) {
        cin >> u >> v >> w;
        u--; v--;
        G[u].emplace_back(v,w);
        rG[v].emplace_back(u,w);
    }

    vector<ll> Dis, rDis;
    calc(n, 0, G, Dis);
    calc(n, 1, rG, rDis);

    assert(Dis[1] == rDis[0]);
    ll sA = Dis[1];

    vector<bool> sE(m);
    vector<vector<pil>> sG(n), rsG(n);
    for(int i = 0; i < m; i++) {
        int u = get<0>(edge[i]);
        int v = get<1>(edge[i]);
        int w = get<2>(edge[i]);
        if (Dis[u]+rDis[v]+w == sA) {
            sE[i] = true;
            sG[u].emplace_back(v,w);
            rsG[v].emplace_back(u,w);
        }
    }

    vector<HASH> cnt, rcnt;
    run(n, 0, sG, cnt);
    run(n, 1, rsG, rcnt);

    vector<bool> isB(m,false);
    for(int i = 0; i < m; i++) if (sE[i]) {
        int u = get<0>(edge[i]);
        int v = get<1>(edge[i]);
        isB[i] = cnt[u] * rcnt[v] == cnt[1];
        // cerr _ u _ v _ w _ isB[i] _ endl;
    }

    for(int i = 0; i < m; i++) {
        int u = get<0>(edge[i]);
        int v = get<1>(edge[i]);
        int w = get<2>(edge[i]);
        ll nsA = Dis[v] + rDis[u] + w;
        cerr _ sE[i] _ isB[i] _ nsA _ sA _ endl; if (nsA < sA)
            cout << "HAPPY" << endl;
        else if (!isB[i])
            cout << "SOSO" << endl;
        else
            cout << "SAD" << endl;
    }

    return 0;
}