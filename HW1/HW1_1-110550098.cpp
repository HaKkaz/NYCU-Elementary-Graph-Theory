#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define fast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define _ <<' '<<
#define ALL(v) v.begin(),v.end()
#define ft first
#define sd second
#define tiii tuple<int,int,int>
using ll = long long;
using ld = long double;
using pii = pair<int,int>;

const int MAXN=1005;
int adj[MAXN][MAXN];
int in[MAXN] , out[MAXN];

signed main(){
	fast;
	int n,m; cin >> n >> m ;
	while(m--){
		int u, v, w;
		cin >> u >> v >> w;
		adj[u][v] = w;
		out[u]++;
		in[v]++;
	}
	for(int i=1 ; i<=n ; ++i){
		for(int j=1 ; j<=n ; ++j){
			cout << adj[i][j] << " \n"[j==n];
		}
	}
	for(int i=1 ; i<=n ; ++i){
		cout << in[i] << ' ' << out[i];
		if(i != n) cout << '\n';
	}
}