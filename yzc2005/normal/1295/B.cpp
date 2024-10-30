#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7, N = 1e5 + 10;
const int inf = 0x3f3f3f3f;
#define rg register
#define fu(i, a, b) for(rg int i = a, I = (b) + 1; i < I; ++i)
#define fd(i, a, b) for(rg int i = a, I = (b) - 1; i > I; --i)
#define go(G, u) for(rg int o = G.head[u], v = G.to[o]; o; o = G.nxt[o], v = G.to[o])
#define reset(a) memset(a, 0, sizeof(a))
#define finish(a) return a, 0;
typedef pair<int, int> P;
typedef long long ll;
template <class T> inline void read(T &x) {
    x = 0; T f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') f = ch == '-' ? -1 : 1, ch = getchar();
    while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    x *= f;
} 
template <class T> inline void ckmax(T &a, T b) {a = max(a, b);}
template <class T> inline void ckmin(T &a, T b) {a = min(a, b);}
template <class T> inline void addmod(T &a, T b) {a = (a + b) % mod;}

int t, n, x, sum[N];
char s[N];

inline int get(int x) {
	x %= n;
	if(!x) x = n;
	return x;
}

//sum[n] * (i - 1) / n + sum[i % n] = x;

int main() {
	read(t);
	while(t--) {
		read(n), read(x);
		scanf("%s", s + 1);
		fu(i, 1, n) sum[i] = sum[i - 1] + (s[i] == '0' ? 1 : -1);
		if(!sum[n]) {
			bool flg = 0;
			fu(i, 0, n) if(x == sum[i]) flg = 1;
			puts(flg ? "-1" : "0");
			continue;
		}
		int ans = x == 0;
		fu(i, 1, n) {
			int xx = x - sum[i];
			if(xx % sum[n] == 0 && xx / sum[n] >= 0) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}