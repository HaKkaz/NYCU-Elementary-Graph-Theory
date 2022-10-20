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

const int MAXN = 1e6+60;
array<int,MAXN> dis;
bool vis[MAXN];
vector<int> v[MAXN];
const int INF = 1e18;

signed main(){
	IOS;
	int n,m,k,t;
	cin >> n >> m >> k >> t;
	for(int i=0 ; i<m ; ++i){
		int a,b;
		cin >> a >> b;
		v[a].push_back(b);
	}

	dis.fill(INF);

	queue<int> q;
	for(int i=0 ; i<k ; ++i){
		int x; cin >> x;
		assert(vis[x] == false);
		q.emplace(x);
		vis[x] = true;
		dis[x] = 0;
	}

	while(q.size()){
		auto cur = q.front();
		q.pop();
		for(auto &nxt : v[cur]){
			if(!vis[nxt]){
				dis[nxt] = dis[cur] + 1;
				q.emplace(nxt);
				vis[nxt] = true;
			}
		}
	}

	int ans=0;
	for(int i=1 ; i<=n ; ++i){
		if(dis[i] < t){
			++ans;
		}
	}
	cout << ans << '\n';
}