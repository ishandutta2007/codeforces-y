#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME "std"

class fenv_tree {
  static int f(int x) { return x & -x; }
  vi tr;

  public:
  void add(int x, int v) {
    assert(0 <= x && x + 1 < sz(tr));
    for (x++; x < sz(tr); x += f(x))
      tr[x] += v;
  }
  int get(int x) {
    assert(-1 <= x && x + 1 < sz(tr));
    int res = 0;
    for (x++; x > 0; x -= f(x))
      res += tr[x];
    return res;
  }

  fenv_tree(int n = 0) : tr(n + 1) {}
};

typedef unsigned long long hash;
const hash P = 29;
const int K = 17;
const int MAXN = 1e5 + 1e3;
hash PPOW[MAXN + 1];

struct _node;
struct Up {
  _node *x;
  hash h, hrev;
  Up() : x(0), h(0), hrev(0) {}
  Up(_node *x, hash h, hash hrev) : x(x), h(h), hrev(hrev) {}
};
typedef struct _node {
  _node* ne[26];
  int cnt;
  Up ups[K];
  hash sumhrev;
  int depth;

  _node() : cnt(0), sumhrev(0), depth(0) {
    memset(ne, 0, sizeof ne);
    for (int i = 0; i < K; i++)
      ups[i] = Up();
  }

  pii eulerIds;
  int ordId;
  int sufpos;
} *node;

bool cmp(node v1, node v2) {
  if (v1 == v2) return false;
  assert(v1 && v2);

  for (int i = K - 1; i >= 0; i--)
    if ((v1->depth >= (1 << i)) && (v2->depth >= (1 << i)) && v1->ups[i].h == v2->ups[i].h) {
      v1 = v1->ups[i].x;
      v2 = v2->ups[i].x;
      assert(v1);
      assert(v2);
    }
  assert(v1->ups[0].h != v2->ups[0].h);
  return v1->ups[0].h < v2->ups[0].h;
}

hash geth(node base, int len) {
  hash addk = 1;
  if (len > base->depth) {
    addk = PPOW[len - base->depth];
    len = base->depth;
  }
  hash res = 0;
  for (int i = K - 1; i >= 0; i--)
    if (len >= (1 << i)) {
      res = res * PPOW[1 << i] + base->ups[i].h;
      base = base->ups[i].x;
      len -= 1 << i;
    }
  return res * addk;
}
hash gethr(node base, int step, int len) {
  step = base->depth - step - len;
  assert(step >= 0);
  for (int i = K - 1; i >= 0; i--)
    if (step >= (1 << i)) {
      base = base->ups[i].x;
      step -= 1 << i;
    }

  hash res = base->sumhrev;
  assert(0 <= len && len <= MAXN);
  hash ck = PPOW[len];
  for (int i = K - 1; i >= 0; i--)
    if (len >= (1 << i)) {
      base = base->ups[i].x;
      len -= 1 << i;
    }
  res -= base->sumhrev * ck;
  return res;
}
bool cmp2(node v1, node v2) { // First tree (reverse path), second tree (direct path)
  int clen = 0;
  for (int i = K - 1; i >= 0; i--) {
    if (((clen + (1 << i)) <= v2->depth) && (v1->depth >= (1 << i)) && v1->ups[i].h == gethr(v2, clen, (1 << i))) {
      v1 = v1->ups[i].x;
      clen += 1 << i;
      assert(v1);
    }
  }
  if (clen >= v2->depth) return false;
  assert(v1->ups[0].h != gethr(v2, clen, 1));
  return v1->ups[0].h < gethr(v2, clen, 1);
}
class Tree {
  vector<node> ns;

  public:
  Tree() : ns(1, new _node()) {
    ns[0]->cnt++; 
  }
  node add(int v, char c) {
    assert(0 <= v && v < sz(ns));
    assert('a' <= c && c <= 'z');

    node vv = ns[v];
    node x = vv->ne[c - 'a'];
    if (!x) {
      x = vv->ne[c - 'a'] = new _node();
      x->depth = vv->depth + 1;
      x->sumhrev = vv->sumhrev * P + c;

      x->ups[0] = Up(vv, c, c);
      for (int i = 1; i < K; i++) {
        Up a = x->ups[i - 1];
        Up b;
        if (a.x) b = a.x->ups[i - 1];
        assert(0 <= (1 << (i - 1)) && (1 << (i - 1)) <= MAXN);
        x->ups[i] = Up(
          b.x,
          a.h * PPOW[1 << (i - 1)] + b.h,
          b.hrev * PPOW[1 << (i - 1)] + a.hrev
        );
      }
    }
    ns.pb(x);
    return x;
  }

  private:
  vector<pair<hash, node> > hnodes;
  vector<node> ord;
  int ctim;
  void dfs(node v) {
    if (!v) return;
    v->ordId = sz(ord);
    ord.pb(v);
    v->eulerIds.first = ctim++;
    for (int i = 0; i < 26; i++)
      dfs(v->ne[i]);
    v->eulerIds.second = ctim++;
  }

  fenv_tree euler;
  vector<node> sufarr;
  vi sufpos;
  fenv_tree sufsum;

  public:
  void precalc(int type) {
    if (type == 1) {
      ctim = 0;
      ord.clear();
      dfs(ns[0]);
      hnodes.resize(sz(ns));
      for (int i = 0; i < sz(ns); i++)
        hnodes[i] = mp(ns[i]->sumhrev, ns[i]);
      stable_sort(hnodes.begin(), hnodes.end());
      euler = fenv_tree(ctim);
    }
    assert(ns[0]->cnt == 1);

    if (type == 2) {
      sufarr = ns;
      stable_sort(sufarr.begin(), sufarr.end(), cmp);
      for (int i = 0; i < sz(sufarr); i++) {
        sufarr[i]->sufpos = i;
      }
      sufsum = fenv_tree(sz(sufarr));
    }
    addCnt(ns[0], type);
  }

  private:
  vector<pii> sufpc;
  public:
  void calcSufs(const Tree &t1) {
    int p1 = 0;
    sufpc = vector<pii>(sz(t1.ord));
    for (int i = 0; i < sz(t1.ord); i++) {
      const node &v = t1.ord[i];
      while (p1 < sz(sufarr) && cmp2(sufarr[p1], v)) p1++;

      int L = p1, R = sz(sufarr);
      if (L < R) {
        if (sufarr[p1]->depth < v->depth || geth(sufarr[p1], v->depth) != v->sumhrev) R = L;
      }
      while (L + 1 < R) {
        int M = (L + R) / 2;
        if (sufarr[M]->depth < v->depth || geth(sufarr[M], v->depth) != v->sumhrev) R = M;
        else L = M;
      }
      sufpc[i] = mp(p1, R);
    }
  }
  void addCnt(node v, int type) {
    if (type == 1) {
      euler.add(v->eulerIds.first, 1);
      euler.add(v->eulerIds.second, -1);
    } else {
      sufsum.add(v->sufpos, 1);
    }
  }
  int getParSum(node v) {
    return euler.get(v->eulerIds.first);
  }
  node getHashRev(hash h) {
    int i = lower_bound(hnodes.begin(), hnodes.end(), mp(h, (node)0)) - hnodes.begin();
    if (i >= sz(hnodes)) return 0;
    if (hnodes[i].first != h) return 0;
    return hnodes[i].second;
  }
  node getV(int x) { return ns[x]; }
  int getSufStartWith(node t2) {
    int a = sufpc[t2->ordId].first;
    int b = sufpc[t2->ordId].second;
    return sufsum.get(b - 1) - sufsum.get(a - 1);
  }
};

struct Op {
  int t, v;
  char c;
};

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);
  #endif

  PPOW[0] = 1;
  for (int i = 1; i <= MAXN; i++)
    PPOW[i] = PPOW[i - 1] * P;

  int n;
  while (scanf("%d", &n) >= 1) {
    Tree t1, t2;
    ll ans = 1;
    vector<Op> ops(n);

    int _m1 = 1, _m2 = 1;
    for (int step = 0; step < n; step++) {
      Op &o = ops[step];
      scanf("%d%d %c", &o.t, &o.v, &o.c), o.v--;
      assert(1 <= o.t && o.t <= 2);
      assert('a' <= o.c && o.c <= 'z');
      if (o.t == 1) {
        assert(0 <= o.v && o.v < _m1);
        _m1++;
        t1.add(o.v, o.c);
      } else {
        assert(0 <= o.v && o.v < _m2);
        _m2++;
        t2.add(o.v, o.c);
      }
    }
    t1.precalc(1);
    t2.precalc(2);

    t2.calcSufs(t1);

    int m1 = 0, m2 = 0;
    for (int step = 0; step < n; step++) {
      Op &o = ops[step];
      if (o.t == 1) {
        m1++;
        node x = t1.getV(m1);
        assert(x);
        t1.addCnt(x, 1);
        ans += t2.getSufStartWith(x);
      } else if (o.t == 2) {
        m2++;
        node x = t2.getV(m2);
        assert(x);
        t2.addCnt(x, 2);

        node y = x;
        hash ch = 0;
        for (int i = K - 1; i >= 0; i--) if ((1 << i) <= y->depth) {
          assert(0 <= (1 << i) && (1 << i) <= MAXN);
          hash h = ch * PPOW[1 << i] + y->ups[i].h;
          if (t1.getHashRev(h)) {
            ch = h;
            y = y->ups[i].x;
          }
        }
        ans += t1.getParSum(t1.getHashRev(ch));
      }
      printf("%I64d\n", ans);
    }
    #ifndef DEBUG
    break;
    #endif
  }
  eprintf("%d\n", clock());
  return 0;
}