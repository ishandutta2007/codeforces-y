#pragma GCC optimize("O2")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,ssse3,tune=native")
#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
using namespace std;
using ll = long long;
//using arr = array;
using pi = pair<int, int>;
using vi = vector<int>;
using vpi = vector<pi>;
using ld = long double;
#include<bits/extc++.h>
using namespace __gnu_pbds;
using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
const int maxn = 404, mod = (119<<23)+1, lg = 19;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void solve() {
	int n;
	cin >> n;
	vpi a(n);
	for(auto &i : a) cin >> i.first >> i.second;
	for(int i = 0; i < n; i++) if(a[i].first<a[i].second) {cout << "NO\n";return;}
	for(int i = 1; i < n; i++) {
		auto [p1, c1] = a[i-1];
		auto [p, c] = a[i];
		int d = p-p1;
		int t = c-c1;
		if(t > d) {cout << "NO\n";return;}
		if(p1 > p) {cout << "NO\n";return;}
		if(c1 > c) {cout << "NO\n";return;}
	}
	cout << "YES\n";
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}