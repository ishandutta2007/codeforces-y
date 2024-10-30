#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define sqr(x) ((x) * (x))

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

const int INF = 1e9;

int h, w;
vvi f;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

bool check(int x, int y) { return 0 <= x && x < w && 0 <= y && y < h && f[y][x]; }

vvi was;

double sumx, sumy;
int cnt;
void dfs1(int x, int y) {
  if (was[y][x] >= 1) return;

  was[y][x] = 1;
  sumx += x; sumy += y;
  cnt++;

  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (!check(nx, ny)) continue;
    dfs1(nx, ny);
  }
}

vector<pii> pts;

void dfs2(int x, int y) {
  if (was[y][x] >= 2) return;
  was[y][x] = 2;
  bool bord = false;
  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if (!check(nx, ny)) { bord = true; continue; }
    dfs2(nx, ny);
  }
  if (bord) {
    pts.pb(mp(x, y));
  }
}

int main() {
  #ifdef DEBUG
  freopen("std.in", "r", stdin);
  freopen("std.out", "w", stdout);
  #endif

  while (scanf("%d", &h) >= 1) {
    w = h;
    f = vvi(h, vi(w));
    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
      scanf("%d", &f[y][x]);

    vvi f2(h, vi(w, 0));
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        for (int dx = -2; dx <= 2; dx++)
        for (int dy = -2; dy <= 2; dy++) {
          if (x + dx < 0 || x + dx >= w) continue;
          if (y + dy < 0 || y + dy >= h) continue;
          f2[y][x] += f[y + dy][x + dx];
        }
        f2[y][x] = (f2[y][x] >= 10);
      }                         
    }
    f = f2;

    #ifdef DEBUG
    FILE *out = fopen("std.res", "w");
    fprintf(out, "%d %d\n", h, w);
    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
      fprintf(out, "%d%c", f[y][x], "\n "[x + 1 < w]);
    fclose(out);
    #endif

    int c1 = 0, c2 = 0;
    was = vvi(h, vi(w, 0));

    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++) if (!was[y][x] && f[y][x]) {
      sumx = 0, sumy = 0;
      cnt = 0;
      dfs1(x, y);
      assert(cnt > 0);
      if (cnt < 140) continue;
      sumx /= cnt, sumy /= cnt;


      pts.clear();
      dfs2(x, y);

      double maxd = 0;
      for (int a = 0; a < sz(pts); a++)
      for (int b = 0; b < sz(pts); b++)
        maxd = max(maxd, (double)(sqr(pts[a].first - pts[b].first) + sqr(pts[a].second- pts[b].second)));
      maxd = sqrt(maxd);

      double minw = 1e100;
      for (int A = -5; A <= 5; A++)
      for (int B = -5; B <= 5; B++) if (A || B) {
        double l = 1e100, r = -1e100;
        for (int i = 0; i < sz(pts); i++) {
          double c = A * pts[i].first + B * pts[i].second;
          l = min(l, c);
          r = max(r, c);
        }
        double D = sqrt(A * A + B * B);
        l /= D;
        r /= D;
        minw = min(minw, r - l);
      }

      double k = maxd / minw;
      eprintf("%.2lf %.2lf;  %.2lf\n", minw, maxd, k);
      if (k > 1.12)
        c2++;
      else
        c1++;
    }
/*      for (int y1 = 0; y1 < h; y1++) {
      for (int x1 = 0; x1 < w; x1++) {
        printf("%c", " H"[was[y1][x1] == 2]);
      }
      printf("\n");
      }*/
      printf("%d %d\n", c1, c2);
  }
  return 0;
}