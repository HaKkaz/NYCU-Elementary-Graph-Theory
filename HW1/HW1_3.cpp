#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,fast-math,unroll-loops")
#define int long long
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

int n,m;

bool check(vector<int> &deg){
	if(accumulate(ALL(deg) , 0ll) & 1ll) return false;

	sort(deg.begin()+1 , deg.end());

	vector<int> psum(n+1,0);
	for(int i=1 ; i<=n ; ++i){
		psum[i] = psum[i-1] + deg[i];
		if(deg[i] < 0 || deg[i] >= n) return false;
	}

	int deg_sum = 0 ;
	for(int kk=n,k=1 ; k<=n ; --kk,++k){
		deg_sum += deg[kk];
		auto it = lower_bound(deg.begin(),deg.begin()+kk-1 , k);
		int min_sum = 0;
		int p = it-deg.begin();
		min_sum = psum[p-1] + k*(n-p);
		if(deg_sum > min_sum){
			return false;
		}
	}
	assert(accumulate(ALL(deg) , 0ll) == psum[n]);
	return (deg_sum % 2 == 0);
}


signed main(){
	IOS;
	int t=1;
	cin >> t;
	while(t--){
		cin >> n >> m;
		vector<int> deg(n+1,0);
		for(int i=1 ; i<=n ; ++i){
			cin >> deg[i];
		}
		
		for(int i=0 ; i<m ; ++i){
			int a,b; cin >> a >> b;
			deg[a]-- , deg[b]--;
		}

		cout << (check(deg) ? "Yes" : "No") << '\n';
	}
}