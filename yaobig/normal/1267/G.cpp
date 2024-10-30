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

const int maxn = 100;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;

const int MAXA = 10000;

int a[maxn+5];
db dp[maxn+5][MAXA+5];

int main()
{
    int n,x; scanf("%d%d",&n,&x);
    rep(i,1,n) scanf("%d",&a[i]);
    int tot = 0;
    dp[0][0] = 1.0;
    rep(i,1,n) 
    {
        per(c,0,i-1) rep(s,0,tot) dp[c+1][s+a[i]] += dp[c][s]*(c+1)/(n-c);
        tot += a[i];
    }
    db ans = 0;
    rep(c,1,n) rep(s,0,tot) ans += dp[c][s]*min((db)s/c, ((db)n/c+1)*x/2);
    printf("%.17f\n",ans);
    return 0;
}