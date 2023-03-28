#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,fast-math,unroll-loops")
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
const int maxn = 1200;
const int inf = 1e9+7;
struct Dinic//1-base
{
	struct Edge
	{
		int to , cap , rev;
		Edge(){}
		Edge(int _to , int _cap , int _rev):to(_to) , cap(_cap) , rev(_rev){}	
	};
	vector<Edge> G[maxn];
	int n , s , t;
	void add_edge(int a , int b , int cap){
		G[a].push_back({b , cap , SZ(G[b])});
		G[b].push_back({a , 0 , SZ(G[a])-1});
	}
	void init(int _n , int _s , int _t){
		n = _n , s = _s , t = _t;
		for(int i=0 ; i<=n ; ++i) G[i].clear();
	}
	int level[maxn] , iter[maxn];
	void bfs(){
		fill(level , level+maxn , -1);
		level[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int now = q.front(); q.pop();
			for(Edge e : G[now]){
				if(e.cap > 0 && level[e.to] == -1){
					level[e.to] = level[now]+1;
					q.push(e.to);
				}
			}
		}
	}
	int dfs(int now , int flow){
		if(now == t) return flow;
		for(int &i = iter[now] ; i<SZ(G[now]) ; ++i){
			assert(i < SZ(G[now]));
			Edge &e = G[now][i];
			if(e.cap > 0 && level[e.to] == level[now]+1){
				int ret = dfs(e.to , min(e.cap , flow));
				if(ret > 0){
					e.cap -= ret;
					G[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	int flow(){
		int ret = 0 ;
		while(true){
			bfs();
			if(level[t] == -1) break;
			fill(iter , iter+maxn , 0);
			int tmp;
			while((tmp=dfs(s,inf)) > 0){
				ret += tmp;
			}
		}
		return ret;
	}
}FLOW;
signed main(){
	IOS;
	int n , m , k;
	cin >> n >> m >> k;
	//
	int super_start = n+m+1;
	int super_end = n+m+10;
	int med = n+m+2;
	FLOW.init(n+m+20 , super_start , super_end);
	//
	FLOW.add_edge(super_start , med , k);
	for(int i=1 ; i<=n ; ++i){
		FLOW.add_edge(super_start , i , 1);
		FLOW.add_edge(med , i , 1);
	}
	//monster = [n+1 , n+m]
	for(int i=1 ; i<=m ; ++i){
		FLOW.add_edge(n+i , super_end , 1);
	}
	for(int from=1 ; from<=n ; ++from){
		int num; cin >> num;
		while(num--){
			int _to ; cin >> _to;
			FLOW.add_edge(from , n+_to , 1);
		}
	}
	cout << FLOW.flow() << '\n';
}