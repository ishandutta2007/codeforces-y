#include <bits/stdc++.h>
using std::max;

const int N = 200054;

char s[N];
int n, q;

namespace ST {
	// lydsy1095
	#define segc int M = L + R - 1 >> 1, lc = id << 1, rc = lc | 1

	struct node {
		/*
		l: ')', r: '(', lc, rc: '))...)((...(',
		ld: '((...(' - '))...)', rd: '))...)' - '((...('
		*/
		int l, r, lc, rc, ld, rd, ans;
		node () {}
		node (int ch) {
			switch (ch) {
				case 40: l = 0, r = 1, lc = rc = ans = 1, ld = 1, rd = 0; break;
				case 41: l = 1, r = 0, lc = rc = ans = 1, ld = 0, rd = 1; break;
			}
		}
	} x[N * 4];

	inline void update(node &ret, const node &x, const node &y) {
		ret.l = max(x.l, x.l - x.r + y.l);
		ret.r = max(y.r, y.r - y.l + x.r);
		ret.lc = max({x.lc, x.l - x.r + y.lc, x.l + x.r + y.ld});
		ret.rc = max({y.rc, y.r - y.l + x.rc, y.r + y.l + x.rd});
		ret.ld = max(x.ld, y.ld + x.r - x.l);
		ret.rd = max(y.rd, x.rd + y.l - y.r);
		ret.ans = max({x.ans, y.ans, x.rc + y.ld, x.rd + y.lc});
	}

	void build(int id, int L, int R) {
		if (L == R) {x[id] = node(s[L]); return;}
		segc; build(lc, L, M), build(rc, M + 1, R);
		update(x[id], x[lc], x[rc]);
	}

	void adj(int id, int L, int R, int h) {
		if (L == R) {x[id] = node(s[L]); return;}
		segc; h <= M ? adj(lc, L, M, h) : adj(rc, M + 1, R, h);
		update(x[id], x[lc], x[rc]);
	}
}

int main() {
	int u, v;
	scanf("%d%d%s", &n, &q, s + 1), n = 2 * (n - 1);
	ST::build(1, 1, n), printf("%d\n", ST::x[1].ans);
	for (; q; --q) {
		if (scanf("%d%d", &u, &v), s[u] != s[v])
			s[u] ^= 1, ST::adj(1, 1, n, u),
			s[v] ^= 1, ST::adj(1, 1, n, v);
		printf("%d\n", ST::x[1].ans);
	}
	return 0;
}