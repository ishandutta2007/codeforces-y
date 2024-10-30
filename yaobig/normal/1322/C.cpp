#include "bits/stdc++.h"
#define rep(i,a,n) for(auto i=a;i<=n;i++)
#define per(i,a,n) for(auto i=n;i>=a;i--)
#define pb push_back
#define mp make_pair
#define FI first
#define SE second
#define all(A) A.begin(),A.end()
#define sz(A) (int)A.size()
template<class T> inline bool chmax(T &a, T b) {if(a<b) {a=b; return 1;} return 0;}
template<class T> inline bool chmin(T &a, T b) {if(b<a) {a=b; return 1;} return 0;}
using namespace std;

string to_string(const string& s) {return '"' + s + '"';}
string to_string(const char* s) {return to_string((string) s);}
template<typename A, typename B> string to_string(pair<A, B> p) {return "(" + to_string(p.FI) + ", " + to_string(p.SE) + ")";}
template<typename A> string to_string(A v) 
{
    bool first = 1;
    string res = "{";
    for(const auto &x: v) 
    {
        if (!first) res += ", ";
        first = 0;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() {cerr << endl;} 
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) 
{
    cerr << " " << to_string(H);
    debug_out(T...);
}
#ifndef ONLINE_JUDGE
    #define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
    #define debug(...) if(0) puts("No effect.")
#endif

using ll = long long;
//using LL = __int128;
using pii = pair<int,int>;
using vi = vector<int>;
using db = double;
using ldb = long double;

const int maxn = 500'000;
const int inf = 0x3f3f3f3f;
const int mod = 1'000'000'007;

vi e[maxn+5];
ll a[maxn+5];

int main()
{
    int cas; scanf("%d",&cas); while(cas--)
    {
        int n,m; scanf("%d%d",&n,&m);
        rep(i,1,n) scanf("%lld",&a[i]);
        rep(i,1,n) e[i].clear();
        rep(i,1,m)
        {
            int x,y; scanf("%d%d",&x,&y);
            e[x].pb(y);
        }
        static vi mark,bel,to;
        mark.assign(m+1,0);
        to.assign(m+1,0);
        bel.assign(n+1,0);
        int tot = 0;
        rep(i,1,n)
        {
            for(auto v: e[i])
            {
                int &s = bel[v];
                if(mark[s]!=i) mark[s] = i, to[s] = ++tot;
                s = to[s];
            }
        }
        static vector<ll> sum; sum.assign(tot+1,0);
        rep(i,1,n) sum[bel[i]] += a[i];
        ll ans = 0;
        rep(i,1,tot) ans = __gcd(ans,sum[i]);
        printf("%lld\n",ans);
    }
    return 0;
}