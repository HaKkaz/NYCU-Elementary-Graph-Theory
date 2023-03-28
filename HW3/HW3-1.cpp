#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
#include<bits/stdc++.h>
using namespace std;
#define _ <<' '<<
#define ALL(v) v.begin(),v.end()
#define ft first
#define sd second
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;
using umap = unordered_map<int,int>;
const int INF = 2100000000;
const int maxn = 1e5+50;


inline int read(){
	int res=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') res=(res<<3)+(res<<1)+(ch^48),ch=getchar();
	return res;
}

array<int,maxn> a{};

void solve(){
	int n = read() , m = read();
	vector< vector<pii> > spec(n, vector<pii>{});

	for(int i=0 ; i<n ; ++i) a[i] = read();
	while(m--){
		int a=read(), b=read(), w=read();
		--a,--b;
		spec[a].emplace_back(b,w);
		spec[b].emplace_back(a,w);
	}

	int mn = a[0] , who = 0;
	vector< bool > used(n,false);
	used[0] = true;


	int pt = 0;
	vector<pii> duty(n-1);
	for(int i=1 ; i<n ; ++i){
		duty[i-1] = {a[i] , i};
	}
	sort(ALL(duty));

	priority_queue< pii, vector<pii>, greater<pii> > can;
	for(auto &[to , wei] : spec[0]){
		can.emplace(wei , to);
	}

	ll ans=0;
	for(int i=1 ; i<n ; ++i){
		while(can.size() && used[can.top().sd]) can.pop();
		while(pt < n-1 && used[duty[pt].sd]) ++pt;

		int A = mn + (duty[pt].ft);
		int B = can.empty() ? INF : can.top().ft;

		auto add = [&](int use, int val){
			used[use] = true;
			ans += val;
			for(auto &[to , wei] : spec[use]){
				if(!used[to])
					can.emplace(wei , to);
			}
			if(a[use] < mn){
				mn = a[use];
				who = use;
			}
		};

		if(A > B){
			auto [wei , b] = can.top();
			can.pop();
			add(b,B);
		}
		else{
			int to = duty[pt++].sd;
			add(to,A);
		}
	}
	printf("%lld\n",ans);
}

signed main(){
	int t=1;
	cin >> t;
	while(t--){
		solve();
	}
}