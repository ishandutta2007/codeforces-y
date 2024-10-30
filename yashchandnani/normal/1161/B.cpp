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
vi pi(const vi& s) {
	vi p(sz(s));
	repA(i,1,sz(s)-1) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}
vi g[100009],s,phi;
map<vi,int> m;
int t=1;
int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	pre();
	int n;cin>>n;
	int q;cin>>q;
	rep(i,q){
		int a,b;cin>>a>>b;
		g[a].pb((b-a+n)%n);
		g[b].pb((a-b+n)%n);
	}
	repA(i,1,n){
		sort(all(g[i]));
		if(m.find(g[i])==m.end()) m[g[i]]=t++;
		s.pb(m[g[i]]);
	}
	repA(i,1,n) s.pb(m[g[i]]);
	phi = pi(s);
	repA(i,n,2*n-2) if(phi[i]>=n){
		cout<<"Yes";
		return 0;
	}
	cout<<"No";
	return 0;
}