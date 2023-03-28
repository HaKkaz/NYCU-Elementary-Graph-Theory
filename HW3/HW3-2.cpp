#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define fast ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using pii = pair<int, int>;

const int maxn = 2e5 + 50;
const int INF = 1e18;
vector<pii> rG[maxn];
vector<vector<int>> dis(3);
int n;

void dijkstra(int st, int id) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.emplace(0, st);
	dis[id][st] = 0;
	while (pq.size()) {
		auto [dd, cur] = pq.top();
		pq.pop();
		if (dd != dis[id][cur]) continue;
		for (auto &[nxt, w] : rG[cur]) {
			if (dis[id][nxt] > dis[id][cur] + w) {
				dis[id][nxt] = dis[id][cur] + w;
				pq.emplace(dis[id][nxt], nxt);
			}
		}
	}
}

void task1() {
	for (int i = 1; i <= n; ++i) {
		if (dis[0][i] >= INF) cout << -1;
		else cout << dis[0][i];
		cout << " \n"[i == n];
	}
}

void task2() {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for (int i = 2; i <= n - 1; ++i) {
		pq.emplace(dis[0][i] + dis[1][i], i);
		dis[2][i] = dis[0][i] + dis[1][i];
	}
	pq.emplace(dis[1][1] , 1);
	dis[2][1] = dis[1][1];
	pq.emplace(dis[0][n] , n);
	dis[2][n] = dis[0][n];

	while (pq.size()) {
		auto [dd, cur] = pq.top();
		pq.pop();
		if (dd != dis[2][cur]) continue;
		for (auto &[nxt, w] : rG[cur]) {
			if (dis[2][nxt] > dis[2][cur] + w) {
				dis[2][nxt] = dis[2][cur] + w;
				pq.emplace(dis[2][nxt], nxt);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (dis[2][i] >= INF) cout << -1;
		else cout << dis[2][i];
		cout << " \n"[i == n];
	}
	
}

void solve() {
	int m, k;
	cin >> n >> m >> k;
	for (int i=1 ; i<=n ; ++i) {
		rG[i].clear();
	}
	dis[0] = vector<int>(n + 1, INF);
	dis[1] = vector<int>(n + 1, INF);
	dis[2] = vector<int>(n + 1, INF);
	for (int i = 0; i < m; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		rG[b].emplace_back(a, w);
	}
	dijkstra(1, 0);
	dijkstra(n, 1);
	if (k == 1) task1();
	if (k == 2) task2();
}

signed main() {
	fast;
	int T, sub; cin >> T >> sub;
	while (T--) solve();
}