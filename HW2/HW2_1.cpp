// #pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
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

bool used[20];
vector<string> str, tmp;
int n;
string cur = "" , ans = "";

string calc(string cur, string add) {
	const int N = cur.size();
	const int M = add.size();
	string ret=add;
	for(int i = N-1; i >= 0; --i) {
		if(N-i > (int)add.size()) break;
		if(cur.substr(i, N-i) == add.substr(0, N-i)) {
			ret = add.substr(N-i, M-N+i);
		}
	}
	// cout << cur << ' ' << add << ' ' << ret << endl;
	return ret;
}

void solve(int id) {
	if(id == n) {
		if(ans.empty() || cur.size() < ans.size() || 
			(cur.size() == ans.size() && cur < ans)) {
			ans = cur;
		}
		return ;
	}

	for(int i = 0; i < n; ++i) {
		if(!used[i]){
			string ori = cur;
			used[i] = 1;
			string add = calc(cur , str[i]);
			cur += add;

			solve(id + 1);

			used[i] = 0;
			cur = ori;
		}
	}

}

signed main(){
	fast;
	cin >> n;
	str.resize(n);
	for(auto &s : str) {
		cin >> s;
	}

	sort(ALL(str), [](string a, string b) {
		return a.size() < b.size();
	});
	for(int i = 0; i < n; ++i) {
		bool ok = true;
		for(int j = i+1; j < n; ++j) {
			if(str[j].find(str[i]) != string::npos) {
				ok = false;
			}
		}
		if(ok) {
			tmp.push_back(str[i]);
		}
	}
	swap(str, tmp);
	n = str.size();

	solve(0);


	cout << ans << '\n';
}
/*
18
a
b
c
d
e
f
g
h
i
j
k
l
m
n
o
p
q
r
*/