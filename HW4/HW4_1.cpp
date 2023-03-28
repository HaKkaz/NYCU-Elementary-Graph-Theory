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

const int maxn = 1e6+60;
const int INF = 1E18;
int dis[maxn], color[maxn] ;
vector<pii> G[maxn];

signed main(){
	fast;
	int n, m, p, q, t, T;
	cin >> n >> m >> p >> q >> t >> T;

	for (int i = 1; i <= n; ++i) {
		dis[i] = INF;
		color[i] = -1;
	}

	for (int i = 0; i < m; ++i) {
		int a,b,w; 
		cin >> a >> b >> w;
		G[a].emplace_back(b, w);
	}

	priority_queue<tiii, vector<tiii>, greater<tiii> > pq;
	for (int i = 0; i < p; ++i){
		int x;
		cin >> x;
		dis[x] = 0;
		pq.emplace(0,1,x);
		color[x] = 1;
	}

	for (int i = 0; i < q; ++i) {
		int x;
		cin >> x;
		if (dis[x] >= t) {
			dis[x] = t;
			pq.emplace(t,0,x);
			color[x] = 0;
		}
	}

	while (pq.size()) {
		auto [d, dc , now] = pq.top();
		pq.pop();
		if (d != dis[now] || dc != color[now]) 
			continue;
		for (auto &[nxt, w] : G[now]) {
			int len = (color[now] ? w : 1);
			if ((dis[nxt] > dis[now] + len) or (dis[nxt] == dis[now] + len && color[nxt] == 1)) {
				dis[nxt] = dis[now] + len;
				color[nxt] = color[now];
				pq.emplace(dis[nxt], color[nxt], nxt);
			}	
		}
	}

	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (color[i] && dis[i] <= T)
			++cnt;
	}
	cout << cnt << '\n';
}