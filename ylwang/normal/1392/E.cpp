#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mkp make_pair
#define rint register int
#define INF ((1 << 30) - 1)
#define FI(n) FastIO::read(n)
#define FO(n) FastIO::write(n)
#define Pair pair < int, int >
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(rint i = (k); i >= (j); i--)
#define For(i, k, j) for(rint i = (k); i <= (j); i++)
#define Foe(i, u) for(rint i = lst[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define file(s) freopen(s".in", "r", stdin); freopen(s".out", "w", stdout)
#define int long long
const int P = 1000000000000000000ll; //
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline void mul(int &a, int b) {a = 1ll * a * b % P;}
inline void addmod(int &a, int b) {int t = a + b; a = (t >= P ? t - P : t); }
inline int ksm(int a, int b) {int ans=1; for(;b;b>>=1) {if(b&1) ans=1ll*ans*a%P;a=1ll*a*a%P;}return ans;}
inline int inv(int a) {return ksm(a, P-2);}
namespace FastIO {
    const int SIZE=1<<16; char buf[SIZE], obuf[SIZE], str[64]; int bi=SIZE, bn=SIZE, opt;
    int read(char *s) {
        while (bn) {for (;bi<bn&&buf[bi]<=' ';bi++);if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}
        int sn=0;while (bn) {for (;bi<bn&&buf[bi]>' ';bi++) s[sn++]=buf[bi];if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}s[sn]=0;return sn;
    }
    bool read(int& x) {if(x)x=0;int bf=0,n=read(str); if(!n)return 0; int i=0; if (str[i]=='-') bf=1,i=1; for(x=0;i<n;i++) x=x*10+str[i]-'0'; if(bf) x=-x; return 1;}
    void write(int x) {
        if(!x) obuf[opt++] = '0'; else {if(x<0) obuf[opt++]='-',x=-x;int sn=0; while(x)str[sn++]=x%10+'0',x/=10;for (int i=sn-1;i>=0;i--) obuf[opt++]=str[i];}
        if (opt>=(SIZE>>1)){fwrite(obuf, 1, opt, stdout); opt=0;}
    }
    void write(char x) {obuf[opt++]=x;if (opt>=(SIZE>>1)){fwrite(obuf, 1, opt, stdout); opt=0;}}
    void Fflush() { if (opt) fwrite(obuf, 1, opt, stdout); opt=0;}
};
const int MAXN = 105;
int n, q, a[MAXN][MAXN];
signed main()
{
//	#ifndef ONLINE_JUDGE 
//		file("pro");
//	#endif
	cin >> n;
	int t = 0;
	foR(j, n, 1) if(~j & 1) {
		foR(i, n, 1) a[i][j] = ksm(2, t + n- i);
		t += 2;
	}
	For(i, 1, n) {
		For(j, 1, n) {
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
	fflush(stdout);
	cin >> q;
	
	while(q--) {
		int k; cin >> k;
//		cerr <<k<< endl;
		int x = 1, y = 1;
		cout << x << ' ' << y << endl;
		int h = -1;
		foR(i, 60, 0) if((k >> i) & 1) {
			h = i; break;
		}
		while(x != n || y != n) {
			if(x == n) y++;
			else if(y == n) x++;
			else {
				if(y & 1) {
					if(h >= 0 && (a[x][y+1] >> h) == 1) y++, h--;
					else x++;
				} else {
					if(h >= 0 && (a[x+1][y] >> h) == 1) x++, h--;
					else y++;
				}
				for(; h >= 0 && ((~k) >> h & 1); h--);
			}
			cout << x << ' ' << y << endl;
		}
		fflush(stdout);
	}
    return FastIO::Fflush(), 0;
}