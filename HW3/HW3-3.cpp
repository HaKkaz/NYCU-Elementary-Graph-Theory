#include<bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
const int maxn = 1e5+50;
vector<int> v[maxn];
array<int,maxn> hei{} , par{};

signed main(){
	fast;
	int n; cin >> n ;
	for(int i=1 ; i<n ; ++i){
		int a,b; cin >> a >> b;
		v[a].emplace_back(b);
		v[b].emplace_back(a);
	}

	function<void(int,int)> dfs = [&](int cur , int fa){
		par[cur] = fa;
		for(int &nxt : v[cur]){
			if(nxt != fa){
				dfs(nxt , cur);
				hei[cur] = max(hei[cur] , hei[nxt]+1);
			}
		}
	};

	dfs(1,-1);

	for(int i=1 ; i<=n ; ++i)
		cout << hei[i] << ' ' << par[i] << '\n';
}