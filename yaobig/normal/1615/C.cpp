#include "bits/stdc++.h"
#define rep(i,a,n) for(auto i=a;i<=n;i++)
#define per(i,a,n) for(auto i=n;i>=a;i--)
#define pb push_back
#define mp make_pair
#define FI first
#define SE second
#define all(A) A.begin(),A.end()
#define sz(A) (int)A.size()
template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return 1;} return 0;}
template<class T> bool chmin(T &a, const T &b) {if(b<a) {a=b; return 1;} return 0;}
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

const int maxn = 100000;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;

char s[maxn+5],t[maxn+5];

int main()
{
    int cas; scanf("%d",&cas); while(cas--)
    {
        int n; scanf("%d",&n);
        scanf("%s%s",s+1,t+1);
        rep(i,1,n) s[i] -= '0';
        rep(i,1,n) t[i] -= '0';
        int ans = inf;
        auto solve = [&](int o) {
            static char a[maxn+5];
            rep(i,1,n) a[i] = s[i];
            int cnt[2] = {};
            rep(i,1,n) if(a[i]^t[i]^o) cnt[(int)a[i]]++;
            if(cnt[1]==cnt[0] || cnt[1]==cnt[0]+1)
            {
                int tot = cnt[0]+cnt[1];
                rep(i,1,n)
                {
                    if(a[i]^t[i]^o) a[i] ^= 1;
                    a[i] ^= tot&1;
                }
                int ok = 1;
                rep(i,1,n) if(a[i]!=t[i]) ok = 0;
                if(ok) chmin(ans,tot);
            }
        };
        solve(0);
        solve(1);
        if(ans==inf) puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}