#include <bits/stdc++.h>
using namespace std;
const int inf = 2e9;
const long long INF = 1e18;
#define fu(i, a, b) for(int i = a, I = (b) + 1; i < I; ++i)
#define fd(i, a, b) for(int i = a, I = (b) - 1; i > I; --i)
#define go(G, u) for(int o = G.head[u], v = G.to[o]; o; o = G.nxt[o], v = G.to[o])
#define reset(a) memset(a, 0, sizeof(a))
#define finish(a) a, exit(0)
#define fail puts("NO"), exit(0)
typedef pair<int, int> P;
typedef long long ll;
template <class T> inline void rd(T &x) {
    x = 0; T f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') f = ch == '-' ? -1 : 1, ch = getchar();
    while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    x *= f;
} 
template <class T> inline void ckmax(T &a, T b) {if(a < b) a = b;}
template <class T> inline void ckmin(T &a, T b) {if(a > b) a = b;}
 
const int N = 105;
int n, t;
char s[N];
 
int main() {
	for(rd(t); t; --t) {
		scanf("%s", s + 1); n = strlen(s + 1);
		int fst = 0, lst = 0, cnt = 0;
		fu(i, 1, n) {
			if(s[i] == '1') {
				++cnt;
				if(!fst) fst = i;
				lst = i;
			}
		}
		printf("%d\n", !cnt ? 0 : lst - fst + 1 - cnt);
	}
	return 0;
}