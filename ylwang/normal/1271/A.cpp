#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define reaD() read()
#define pb push_back
#define mkp make_pair
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(register int i = (k); i >= (j); i--)
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define DEBUG fprintf(stderr, "***IAKIOI***\n")
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
const int MOD = 998244353; //
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline void addmod(int &a, int b) {int t = a + b; a = (t >= MOD ? t - MOD : t); }
inline int read() {
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag=-1;
    for(;c>='0'&&c<='9';num=num*10+c-48,c=getchar());
    return num*flag;
}
 
signed main()
{
	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;
	int m1 = min(d, a), m2 = min(d, min(b, c));
	if(e > f) {
		printf("%d\n", m1 * e + min(d - m1, m2) * f);
	} else {
		printf("%d\n", min(d - m2, m1) * e + m2 * f);
	}
    return 0;
}