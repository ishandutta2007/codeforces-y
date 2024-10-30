#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <climits>
#include <cassert>

#include <iostream>

#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <utility>
#include <memory>
#include <bitset>
#include <string>
#include <tuple>
using namespace std;

#define lowbit(x) ((x) & -(x))
#define lson l,mid,id<<1
#define rson mid+1,r,id<<1|1
#define ls id<<1
#define rs id<<1|1
#define MID(l,r) ((l)+(((r)-(l))>>1))
#define fi first
#define se second
#define mk make_pair
#define mt make_tuple
#define pb push_back
#define epb emplace_back
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()

using LL = long long;
//using LL = __int64;
using pii = pair<int, int>;
using pdd = pair<double, double>;
using pLL = pair<LL, LL>;

const int INF = 0x3f3f3f3f;
const LL LINF = 0x3f3f3f3f3f3f3f3f;
const double pi = acos(-1.0);
const double eps = 1e-8;
const int e5 = 100000; // 1e5
const int e6 = 1000000; //1e6;
const int MOD_1e9 = 1000000007; //1e9 + 7
const int MOD_998 = 998244353;
const int MOD = MOD_1e9;

template< typename T = int > inline T read()
{
    char c = '\0';
    bool f = false;
    T x = 0;
    while(c < '0' || '9' < c) {if(c == '-') f = true; c = getchar();}
    while('0' <= c && c <= '9') {x = (x << 1) + (x << 3) + (c & 0xf); c = getchar();}
    if(f) return -x;
    return x;
}
template< typename T > inline void read(T &x) {x = read<T>();}
template< typename T, typename ...Args > inline void read(T &x, Args &...args) {read(x); read(args...);}

template< typename T > inline void get_min(T &x, T y) {if(y < x) x = y;}
template< typename T > inline void get_max(T &x, T y) {if(x < y) x = y;}
template< typename T > inline void get_unique(vector<T> &vec) {sort(all(vec)); vec.erase(unique(all(vec)), vec.end());}

inline int sig(double x) {return x < -eps ? -1 : eps < x;}
LL fp(LL a, LL n, LL mod = MOD)
{
    if(n < 0) a = fp(a, mod - 2, mod), n = -n;
    LL res = 1;
    for(; n; n >>= 1, a = a * a % mod) if(n & 1) res = res * a % mod;
    return res;
}

template< int mod > struct Mint
{
    int x;
    Mint():x(0) {}
    Mint(int _x): x(_x) {if(x < 0 || x >= mod) x %= mod; if(x < 0) x += mod;}
    Mint(LL _x) {if(_x < 0 || _x >= mod) _x %= mod; if(_x < 0) _x += mod; x = _x;}
    Mint operator - () const {return Mint(mod - x);}
    Mint operator + (const Mint &rhs) const {return Mint(x + rhs.x >= mod ? x + rhs.x - mod : x + rhs.x);}
    Mint operator - (const Mint &rhs) const {return Mint(x - rhs.x < 0 ? x - rhs.x + mod : x - rhs.x);}
    Mint operator * (const Mint &rhs) const {return Mint((LL)x * rhs.x % mod);}
    Mint operator / (const Mint &rhs) const {return Mint((LL)x * fp(rhs.x, -1, mod) % mod);}
    bool operator == (const Mint &rhs) const {return x == rhs.x;}
    bool operator != (const Mint &rhs) const {return x != rhs.x;}
    Mint &operator += (const Mint &rhs) {x += rhs.x; if(x >= mod) x -= mod; return *this;}
    Mint &operator -= (const Mint &rhs) {x -= rhs.x; if(x < 0) x += mod; return *this;}
    Mint &operator *= (const Mint &rhs) {x = (LL)x * rhs.x % mod; return *this;}
    Mint &operator /= (const Mint &rhs) {x = (LL)x * fp(rhs.x, -1, mod) % mod; return *this;}
    friend ostream &operator << (ostream &out, const Mint &rhs) {return out << to_string(rhs.x);}
    Mint inv() {return Mint(fp(x, -1, mod));}
    Mint pow(int k) {return Mint(fp(x, k, mod));}
    Mint pow(const Mint &t) {return Mint(fp(x, t.x, mod));}
};

const int maxn = (int) 1e4 + 20;
const int maxm = (int) 2e6 + 20;

void work()
{
    int n;
    read(n);
    int c2, c3;
    c2 = c3 = 0;
    while(n % 2 == 0 || n % 3 == 0)
    {
        if(n % 2 == 0)
        {
            n /= 2;
            c2++;
        }

        if(n % 3 == 0)
        {
            n /= 3;
            c3++;
        }
    }


    if(n != 1 || c2 > c3)
    {
        cout <<-1 <<endl;
    }
    else
    {
        cout <<c3 + c3 - c2 <<endl;
    }
}

int main()
{
#ifdef yukihana0416
freopen("in.txt", "r", stdin);
//freopen("out.txt", "w", stdout);
#endif // yukihana0416

    int tc = 1;
    read(tc);
    for(int ca = 1; ca <= tc; ca++)
    {
//        printf("Case #%d: ", ca);
        work();
    }
    return 0;
}