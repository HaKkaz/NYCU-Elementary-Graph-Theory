#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,fast-math,unroll-loops")
#define int long long
#define pb push_back
#define MP make_pair
#define pii pair<int,int>
#define F first
#define S second
#define SZ(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define LINE cout << "\n---------------\n";
#define endl cout << '\n';
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define debug(x) cerr << #x << " = "  << x << '\n';
using namespace std;

const int maxn = 3e5+50;
vector<int> v[maxn];
int ac[20][maxn] , stamp , in[maxn] , out[maxn] , dep[maxn];

void dfs(int cur , int depth=0){
	dep[cur] = depth;
	in[cur] = stamp++;
	for(int &nxt : v[cur]){
		if(!ac[0][nxt]){
			ac[0][nxt] = cur;
			dfs(nxt , depth+1);
		}
	}
	out[cur] = stamp++;
}

void build(const int &n){
	ac[0][1] = 1 ;
	dfs(1);
	for(int i=1 ; i<20 ; ++i){
		for(int j=1 ; j<=n ; ++j){
			ac[i][j] = ac[i-1][ac[i-1][j]];
		}
	}
}

bool is_ac(int a , int b){
	return in[a] <= in[b] && out[a] >= out[b];
}

int LCA(int a , int b){
	if(is_ac(a,b)) return a;
	if(is_ac(b,a)) return b;
	for(int i=19 ; i>=0 ; --i){
		if(!is_ac(ac[i][a],b))
			a = ac[i][a];
	}
	return ac[0][a];
}

signed main(){
	IOS;
	int n; cin >> n ;
	for(int i=1 ; i<n ; ++i){
		int a,b; cin >> a >> b;
		v[a].emplace_back(b);
		v[b].emplace_back(a);
	}

	build(n);

	int q; cin >> q;
	while(q--){
		int a,b; cin >> a >> b;
		cout << dep[a] + dep[b] - 2*dep[LCA(a,b)] << '\n';
	}
}