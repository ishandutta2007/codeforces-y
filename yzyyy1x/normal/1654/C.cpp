#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define sc second
#define pb push_back
#define ll long long
#define trav(v,x) for(auto v:x)
#define all(x) (x).begin(), (x).end()
#define VI vector<int>
#define VLL vector<ll>
#define pll pair<ll, ll>
#define double long double
//#define int long long
using namespace std;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;//1e9 + 7;

#ifdef LOCAL
void debug_out(){cerr << endl;}
template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
	cerr << " " << to_string(H);
	debug_out(T...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int n;
map<ll, int> cnt;
int las;

void dfs(ll val)
{
	if(las < 0)
		return;
	if(cnt[val] > 0)
	{
		--cnt[val];
		return;
	}
	--las;
	ll tmp = val / 2;
	dfs(tmp), dfs(val - tmp);
}

void sol()
{
	cin >> n;
	cnt.clear();
	ll sum = 0;
	for(int i = 1; i <= n; i++)
	{
		ll x;
		cin >> x;
		cnt[x]++;
		sum += x;
	}
	las = n - 1;
	dfs(sum);
	if(las == 0)
		cout << "YES" << '\n';
	else cout << "NO" << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tt;
	cin >> tt;
	while(tt--)
		sol();
}