#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
#include<bits/stdc++.h>
// #define int long long
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

void solve() {
	int n, m; cin >> n >> m ;
	vector< pii > Es;
	for (int i = 0; i < m; ++i) {
		int a, b; cin >> a >> b;
		--a, --b;
		Es.emplace_back(a,b);
	}

	bool ok = true;
	for (int ee = 1; ee < (1 << m); ++ee) {
		if(!ok) break;
		bitset<15> G[15];
		for (int j = 0; j < m; ++j) {
			if (ee >> j & 1) {
				int a = Es[j].first, b = Es[j].second;
				G[a][b] = G[b][a] = 1;
			}
		}

		bool hav = true;
		while (hav) {
			hav = false;
			for (int i = 0; i < n; ++i) {
				if (G[i].count() == 2) {
					hav = true;
					vector<int> del;
					for (int j = 0; j < n; ++j) {
						if (G[i][j]) 
							del.push_back(j);
					}
					int a = del[0], b = del[1];
					G[a][i] = G[i][a] = 0;
					G[b][i] = G[i][b] = 0;
					G[a][b] = G[b][a] = 1;
				}
			}
		}
		
		//check K_5
		vector<int> k5;
		for(int i = 0; i < n; ++i) {
			if (G[i].count() == 4) {
				k5.push_back(i);
			}
		}
		if (k5.size() == 5) {
			set<int> s;
			for (int &x : k5) {
				s.insert(x);
				for (int i = 0; i < n; ++i) {
					if (G[x][i]) {
						s.insert(i);
					}
				}
			}
			if (s.size() == 5) {
				ok = false;
			}
		}

		//check k_33
		#define piv pair<int,vector<int>>
		vector< piv > k33;
		for (int i = 0; i < n; ++i) {
			if (G[i].count() == 3) {
				vector<int> tmp;
				for (int j = 0; j < n; ++j) {
					if (G[i][j]) {
						tmp.push_back(j);
					}
				}
				k33.emplace_back(i , tmp);
			}
		}

		sort(ALL(k33) , [&](const piv &a , const piv &b) {
			return a.second < b.second;
		});

		if (k33.size() == 6	&& k33[0].sd == k33[1].sd && k33[1].sd == k33[2].sd 
							&& k33[3].sd == k33[4].sd && k33[4].sd == k33[5].sd && k33[2].sd != k33[3].sd) 
		{
			ok = false;
		}
	}

	cout << (ok ? "Yes" : "No") << '\n';
}

signed main(){
	fast;
	int t=1;
	cin >> t;
	while(t--){
		solve();		
	}
}
/* k33
1
6 9
1 2
1 3
1 4
5 2
5 3
5 4
6 2
6 3
6 4
*/