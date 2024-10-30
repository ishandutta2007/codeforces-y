#include <bits/stdc++.h>
using namespace std;


#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

#define rep(i, n)    for(int i = 0; i < (n); ++i)
#define repA(i, a, n)  for(int i = a; i <= (n); ++i)
#define repD(i, a, n)  for(int i = a; i >= (n); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define fill(a)  memset(a, 0, sizeof (a))
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void pre(){


}

void solve(){


}
int a[2009];
int cnt[2009];
int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	pre();
	int n;cin>>n;
	map<int,int> m;
	int ix = 1;
	rep(i,n) {
		int x;cin>>x;
		if(m[x]==0) m[x]=ix,ix++;
		a[i] = m[x];
	}
	ix--;
	int ans = n;
	rep(i,n){
		fill(cnt);
		int d = 0;
		rep(j,n) {
			if(cnt[a[j]]==0) d++;
			cnt[a[j]]++;
		}
		int j = i;
		while(j<n&&d<n-j+i){
			if(cnt[a[j]]==1) d--;
			cnt[a[j]]--;
			j++;
		}
		if(d==n-j+i) ans = min(ans,j-i);
	}
	cout<<ans;
	return 0;
}