#define ENABLE_LL
#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " " 
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)
#define rep(i,n) for (int i=0;i<n;i++)
#define repa(i,n) for (int i=1;i<=n;i++)
#define repi(i,a,b) for (int i=a;i<=b;i++) 
#define repb(i,a,b) for (int i=a;i>=b;i--)
typedef pair < int , int > pr;
typedef pair < pr  , int > prr;
#define L first
#define R second
template <class T> inline bool checkMin(T& a , T b) { return (a > b ? a=b,1 : 0); }
template <class T> inline bool checkMax(T& a , T b) { return (a < b ? a=b,1 : 0); }

const int N = 200005;

struct Dsu{
    int p[N];

    Dsu() {
        rep (i,N) p[i] = i;
    }

    int get(int u) {
        return u == p[u] ? (u) : (p[u] = get(p[u]) );
    }

    void merge(int u, int v) {
        p[ get(u) ] = get(v);
    }
};

int n, m;
int q[N];
int u[N], v[N], w[N];
int s[N];

void init() {
    scanf(II,&n,&m);
    rep (i,n-1) { scanf(III,&u[i],&v[i],&w[i]); u[i]--; v[i]--; }
    w[n-1] = N;
    rep (i,n) s[i] = i;
    sort(s, s + n, [](int a, int b) { return w[a] < w[b]; } );
    rep (i,m) scanf(I,&q[i]);
}

inline int c(int u) { see(u);return u * (u-1) / 2; }

Dsu st;
int sz[N];
int ans[N];
void solve() {
    int pos = 0;
    rep (i,n) sz[i] = 1;
    rep (_i,n-1) {
        int i = s[_i];
        see(i);
        int gu = st.get(u[i]), gv = st.get(v[i]);
        ses(gu);see(gv);
        pos -= c(sz[gu]) + c(sz[gv]);
        st.merge(gu, gv);
        int gn = st.get(gu);
        sz[gn] = sz[gu] + sz[gv];
        pos += c( sz[gn] );
        see(pos);
        ses(w[i]);see(w[s[_i+1]]);
        repi (j,w[i],w[ s[_i+1] ]-1) ans[j] = pos; 
    }
    rep (i,m) printf("%lld ",ans[ q[i] ]);
}


#ifdef ENABLE_LL
#undef int
#endif
int main(){
    init();
    solve();
    return 0;
}