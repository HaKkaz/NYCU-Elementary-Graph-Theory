#include<bits/stdc++.h>
using namespace std;
#define ALL(v) v.begin(),v.end()

const int maxn = 1e6+60;
vector<int> G[maxn];
bitset<maxn> vis;
int mx_dis;

inline int read(){
	int res=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-f; ch=getchar();}
	while(ch>='0'&&ch<='9') res=(res<<3)+(res<<1)+(ch^48) , ch=getchar();
	return res*f;
}

void find_joint(int cur, int dis , int &joint) {
	vis[cur] = 1;
	if(dis > mx_dis && G[cur].size() == 3) {
		mx_dis = dis;
		joint = cur;
	}
	for(int &nxt : G[cur]) {
		if(!vis[nxt]) {
			find_joint(nxt, dis+1 , joint);
		}
	}
}

vector<int> records , Abar , Bbar;
int bar[maxn] , A , B;

bool dfs(int cur) {
	bool have = G[cur].size() == 3;
	bar[cur] = 1;
	vis[cur] = 1;

	int bbar = -1;
	for(int &nxt : G[cur]) {
		if(vis[nxt]) {
			continue;
		}
		bool have_joint = dfs(nxt);
		have |= have_joint;
		if(!have_joint) {
			if(cur == A) {
				Abar.push_back(bar[nxt]);
			}
			else if(cur == B) {
				Bbar.push_back(bar[nxt]);
			}
			else if(G[cur].size() == 3) {
				bbar = bar[nxt];
			}
			else {
				bar[cur] += bar[nxt];
			}
		}
	}
	if(bbar > 0) records.push_back(bbar);
	return have;
}

signed main(){
	int n = read();
	for(int i = 1; i < n; ++i) {
		int a = read(), b = read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	mx_dis = 0, find_joint(1, 0, A) , vis.reset();
	mx_dis = 0, find_joint(A, 0, B) , vis.reset();
	dfs(A);

	int m = read();
	vector<int> key(m);
	for(int &x : key) x = read();

	bool ok = false;
	for(int &Ab : Abar) {
		for(int &Bb : Bbar) {
			vector<int> tmp;
			tmp.push_back(Bb);
			for(int &x : records) tmp.push_back(x);
			tmp.push_back(Ab);
			ok |= (tmp == key);
			reverse(ALL(tmp));
			ok |= (tmp == key);
		}
	}
	puts((ok ? "YES" : "NO"));
}