#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mkp make_pair
#define rint register int
#define INF ((1ll << 62) - 1)
#define FI(n) FastIO::read(n)
#define FO(n) FastIO::write(n)
#define Pair pair < int, int >
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(rint i = (k); i >= (j); i--)
#define For(i, k, j) for(rint i = (k); i <= (j); i++)
#define Foe(i, u) for(rint i = lst[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define file(s) freopen(s".in", "r", stdin); freopen(s".out", "w", stdout)
#define ull unsigned ll
const int P = 1000000007; //
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline void mulmod(int &a, int b) {a = 1ll * a * b % P;}
inline void addmod(int &a, int b) {int t = a + b; a = (t >= P ? t - P : t); }
inline int ksm(int a, int b) {int ans=1; for(;b;b>>=1) {if(b&1) ans=1ll*ans*a%P;a=1ll*a*a%P;}return ans;}
inline int inv(int a) {return ksm(a, P-2);}

inline void printarray(int *a, int n) {For(i, 1, n) fprintf(stderr, "%d ", a[i]); fprintf(stderr, "\n");}
namespace FastIO {
    const int SIZE=1<<16; char buf[SIZE], obuf[SIZE], str[64]; int bi=SIZE, bn=SIZE, opt;
    int read(char *s) {
        while (bn) {for (;bi<bn&&buf[bi]<=' ';bi++);if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}
        int sn=0;while (bn) {for (;bi<bn&&buf[bi]>' ';bi++) s[sn++]=buf[bi];if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}s[sn]=0;return sn;
    }
    bool read(int& x) {if(x)x=0;int bf=0,n=read(str); if(!n) return 0; int i=0; if (str[i]=='-') bf=1,i=1; for(x=0;i<n;i++) x=x*10+str[i]-'0'; if(bf) x=-x; return 1;}
    void write(int x) {
        if(!x) obuf[opt++] = '0'; else {if(x<0) obuf[opt++]='-',x=-x;int sn=0; while(x)str[sn++]=x%10+'0',x/=10;for (int i=sn-1;i>=0;i--) obuf[opt++]=str[i];}
        if (opt>=(SIZE>>1)){fwrite(obuf, 1, opt, stdout); opt=0;}
    }
    void write(char x) {obuf[opt++]=x;if (opt>=(SIZE>>1)){fwrite(obuf, 1, opt, stdout); opt=0;}}
    void Fflush() { if (opt) fwrite(obuf, 1, opt, stdout); opt=0;}
};
const int MAXN = 1e6 + 5;
int n, k, fac[MAXN], invfac[MAXN];
void init() {
	fac[0] = 1; For(i, 1, k + 2) fac[i] = 1ll * fac[i - 1] * i % P;
	invfac[k + 2] = inv(fac[k + 2]);
	foR(i, k + 1, 0) invfac[i] = 1ll * invfac[i+1] * (i + 1) % P;
//	cerr << invfac[0] << endl;
}
int y[MAXN];
inline int f(int n) {
	if(n <= k + 2) return y[n];
	int t = 1, sum = 0;
	For(j, 1, k + 2) mulmod(t, n - j);
	For(i, 1, k + 2) {
//		cerr << i << ' ' << y[i] << ' ' << invfac[i - 1] << ' ' << invfac[k + 1 - i] << endl;
		if((k + 2 - i) % 2 == 0) sum = (sum + 1ll * y[i] * invfac[i - 1] % P * invfac[k + 2 - i] % P * inv(n - i) % P * t % P) % P;
		else sum = (sum - 1ll * y[i] * invfac[i - 1] % P * invfac[k + 2 - i] % P * inv(n - i) % P * t % P + P) % P;
//		cerr << i << ' ' << y[i] << ' ' << sum << endl;
	}
//	cerr << t << ' ' << sum << endl;
	return sum;
}
signed main()
{
    #ifndef ONLINE_JUDGE
        file("pro");
    #endif
    cin >> n >> k;
    init();
	For(i, 1, k + 2)
    	y[i] = (y[i - 1] + ksm(i, k)) % P;
	printf("%d\n", f(n));
    return FastIO::Fflush(), 0;
}
/*
Think twice :
mod ?
INF ?
n = 1 ?
long long ?
Fastio::Fflush() ?
*/