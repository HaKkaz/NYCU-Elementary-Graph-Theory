#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,fast-math,unroll-loops")
// #define int long long
#define pb push_back
#define MP make_pair
#define pii pair<int,int>
#define F first
#define S second
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(),(x).end()
#define LINE cout << "\n---------------\n";
#define endl cout << '\n';
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define debug(x) cerr << #x << " = "  << x << '\n';
using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

const int maxn = 2e5+50;
vector<int> G[maxn];
vector<int> cut;
int low[maxn], dfn[maxn], stp;

void tarjan(int now) {
	int child = 0;
	dfn[now] = low[now] = ++stp;
	for(int &nxt : G[now]) {
		if(!dfn[nxt]) {
			tarjan(nxt), ++child;
			if(low[nxt] >= dfn[now]) {
				if(now != 1) cut.push_back(now);
			}
			else {
				low[now] = min(low[now] , low[nxt]);
			}
		}
		else {
			low[now] = min(low[now], dfn[nxt]);
		}
	}
	if(now == 1 && child > 1) {
		cut.push_back(now);
	}
}

signed main(){
	IOS;
	int n, m; cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	tarjan(1);
	sort(ALL(cut)), cut.resize(unique(ALL(cut)) - cut.begin());
	cout << cut.size() << '\n';
	for(int &it : cut) cout << it << ' ';
}