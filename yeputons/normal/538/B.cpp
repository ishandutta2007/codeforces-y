#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME ""

#ifdef DEBUG
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;

const int inf = 1e9;
const double eps = 1e-9;
const int INF = inf;
const double EPS = eps;

#ifdef DEBUG
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {};
#endif

/*Template end*/

int main() {
  #ifdef DEBUG
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  int n;
  while (scanf("%d", &n) == 1) {
    char s[16];
    snprintf(s, sizeof s, "%d", n);

    vi ans;
    for (int i = 1; i <= 9; i++) {
      int cur = 0;
      for (int i2 = 0; s[i2]; i2++) {
        cur *= 10;
        if (s[i2] >= '0' + i) {
          cur++;
        }
      }
      if (cur) ans.pb(cur);
    }
    printf("%d\n", sz(ans));
    forn (i, sz(ans))
      printf("%d%c", ans[i], "\n "[i + 1 < sz(ans)]);
  }

  return 0;
}