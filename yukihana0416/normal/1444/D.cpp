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
#include <list>
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
#include <functional>
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
using ULL = unsigned long long;
//using LL = __int64;
//using ULL = unsigned __int64;
using pii = pair<int, int>;
using pdd = pair<double, double>;
using pLL = pair<LL, LL>;

const int INF = 0x3f3f3f3f;
const LL LINF = 0x3f3f3f3f3f3f3f3f;
const double DINF = 1e100;
const double pi = acos(-1.0);
const double eps = 1e-8;
const int e5 = 100000; // 1e5
const int e6 = 1000000; //1e6;
const int MOD_1e9 = 1000000007; //1e9 + 7
const int MOD_998 = 998244353;
const int MOD = MOD_998;

template< typename T > inline void get_min(T &x, T y) {if(y < x) x = y;}
template< typename T > inline void get_max(T &x, T y) {if(x < y) x = y;}
template< typename T > inline T get_abs(T x) {if(x < 0) return -x; return x;}
template< typename T > inline void get_unique(vector<T> &vec) {sort(all(vec)); vec.erase(unique(all(vec)), vec.end());}

inline int sig(double x) {return x < -eps ? -1 : eps < x;}
template< typename T > inline LL fp(LL a, T n, int mod = MOD)
{
    if(n < 0) a = fp(a, mod - 2, mod), n = -n;
    LL res = 1;
    for(; n; n >>= 1, a = a * a % mod) if(n & 1) res = res * a % mod;
    return res;
}

template< int mod > class Mint
{
public:
    int x;
    Mint():x(0) {}
    Mint(int _x): x(_x) {if(x < 0 || x >= mod) x %= mod; if(x < 0) x += mod;}
    Mint(LL _x) {if(_x < 0 || _x >= mod) _x %= mod; if(_x < 0) _x += mod; x = _x;}
    Mint operator - () const {return Mint(x == 0 ? x : mod - x);}
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
    Mint inv() const {return Mint(fp(x, -1, mod));}
    Mint pow(int k) const {return Mint(fp(x, k, mod));}
};

class fast_reader
{
private:
    int buff_size;
    char *buff_ptr;
    char *ptr;
    char *tail;
    bool is_open;
    fast_reader(const fast_reader &) = delete;
    fast_reader &operator = (const fast_reader &) = delete;

    inline bool is_digit() const {return '0' <= *ptr && *ptr <= '9';}
    inline bool is_blank() const {return *ptr == ' ' || *ptr == '\n' || *ptr == '\t' || *ptr == '\0';}
    template <typename T> inline void read_i(T &x)
    {
        bool f = false;
        x = 0;
        while(ptr < tail && !is_digit()) {if(*ptr == '-') f = true; ptr++;}
        while(ptr < tail && is_digit()) {x = (x << 1) + (x << 3) + (*ptr & 0xf); ptr++;}
        if(f) x = -x;
    }
    template <typename T> inline void read_f(T &x)
    {
        static char t_buff[1 << 6];
        read(t_buff);
        x = atof(t_buff);
    }
public:
    fast_reader(): buff_size(0), buff_ptr(nullptr), ptr(nullptr), tail(nullptr), is_open(false) {}
    ~fast_reader() {if(is_open) free(buff_ptr);}
    template <typename T> fast_reader &operator >> (T &x) {read(x); return *this;}
    template<typename T, typename ...Args> inline void read(T &x, Args &...args) {read(x); read(args...);}
    inline bool is_end() {while(ptr < tail && is_blank()) ptr++; return ptr >= tail;}

    inline void open_alter(int _base_size = 1 << 24) //2^24B = 16MB
    {
        if(is_open) throw runtime_error("fast reader is reopened!");

        int input_size = 0;
        int call_size = _base_size;
        buff_ptr = (char *) malloc(call_size);
        input_size += fread(buff_ptr, 1, call_size, stdin);
        while(feof(stdin) == 0)
        {
            int recall_size = call_size;
            buff_ptr = (char *) realloc(buff_ptr, call_size + recall_size);
            tail = buff_ptr + call_size;
            input_size += fread(tail, 1, recall_size, stdin);
            call_size += recall_size;
        }
        buff_ptr = (char *) realloc(buff_ptr, input_size);
        ptr = buff_ptr;
        tail = buff_ptr + input_size;
        buff_size = input_size;
        is_open = true;
    }

    inline void read(int &x) {read_i(x);}
    inline void read(unsigned int &x) {read_i(x);}
    inline void read(long long &x) {read_i(x);}
    inline void read(unsigned long long &x) {read_i(x);}
    inline void read(float &x) {read_f(x);}
    inline void read(double &x) {read_f(x);}
    inline void read(char *str)
    {
        while(ptr < tail && is_blank()) ptr++;
        while(ptr < tail && !is_blank()) *str = *ptr++, str++;
        *str = '\0';
    }
    inline void read(string &s)
    {
        while(ptr < tail && is_blank()) ptr++;
        char *pre = ptr;
        while(ptr < tail && !is_blank()) ptr++;
        s = std::move(string(pre, ptr)); //<utility>
    }
}reader;

const int maxn = (int) 5e5 + 5;
const int maxm = (int) 1e6 + 5;

bitset<maxm> dp[1001];

bool DP(int n, const vector<int> &a, vector<int> &part1, vector<int> &part2)
{
    int bias = 0;
    for(const auto &x : a) bias += x;

    dp[0].reset();
    dp[0][bias] = 1;
    for(int i = 0; i < n; i++)
    {
        int x = a[i];
        dp[i + 1] = (dp[i] << x) | (dp[i] >> x);
    }

    if(!dp[n][bias]) return 0;

    part1.clear();
    part2.clear();

    int pre = bias;
    for(int i = n - 1; ~i; i--)
    {
        int x = a[i];
        if(dp[i][pre - x])
        {
            part1.epb(x);
            pre = pre - x;
        }
        else
        {
            part2.epb(x);
            pre = pre + x;
        }
    }

    return 1;
}

bool brute_try(const vector<int> &x1, const vector<int> &x2, const vector<int> &y1, const vector<int> &y2, vector<pii> &res)
{
    vector<int> px, py;
    for(const auto &x : x1) px.epb(x);
    for(const auto &x : x2) px.epb(-x);

    for(const auto &y : y1) py.epb(y);
    for(const auto &y : y2) py.epb(-y);

    int n = x1.size() + x2.size();

    vector<pii> point;
    pii o = mk(0, 0);
    for(int i = 0; i < n * 2; i++)
    {
        if(i % 2) o.fi += px[i >> 1];
        else o.se += py[i >> 1];
        point.epb(o);
    }

    for(int i = 1; i < n * 2; i += 2)
    {
        int a, b, c;
        if(point[i].fi == point[i - 1].fi) a = point[i].fi, b = point[i].se, c = point[i - 1].se;
        else a = point[i].se, b = point[i].fi, c = point[i - 1].fi;
        if(b > c) swap(b, c);

        for(int j = 2; j < n * 2; j += 2)
        {
            int aa, bb, cc;
            if(point[j].fi == point[j - 1].fi) aa = point[j].fi, bb = point[j].se, cc = point[j - 1].se;
            else aa = point[j].se, bb = point[j].fi, cc = point[j - 1].fi;
            if(bb > cc) swap(bb, cc);

            if(b <= aa && aa <= c && bb < a && a < cc) return 0;
            if(b < aa && aa < c && bb <= a && a <= cc) return 0;
        }
    }
    res = point;
    return 1;
}

void work()
{
    int n, m;
    reader >>n;
    vector<int> x(n);
    for(int i = 0; i < n; i++) reader >>x[i];

    vector<int> x1, x2;
    int xf = DP(n, x, x1, x2);

    reader >>m;
    vector<int> y(m);
    for(int i = 0; i < m; i++) reader >>y[i];

    vector<int> y1, y2;
    int yf = DP(m, y, y1, y2);


    if(!xf || !yf || n != m)
    {
        cout <<"No" <<endl;
    }
    else
    {
        sort(all(x1));
        sort(all(x2));

        sort(all(y1));
        sort(all(y2));

        for(int i = 0; i < (1 << 6); i++)
        {
            auto p1 = x1, p2 = x2;
            auto q1 = y1, q2 = y2;

            if(i & 1) swap(p1, p2);
            if(i >> 1 & 1) swap(q1, q2);
            if(i >> 2 & 1) reverse(all(p1));
            if(i >> 3 & 1) reverse(all(p2));
            if(i >> 4 & 1) reverse(all(q1));
            if(i >> 5 & 1) reverse(all(q2));

            vector<pii> res;
            if(brute_try(p1, p2, q1, q2, res))
            {
                cout <<"Yes" <<endl;
                for(auto pr : res)
                    cout <<pr.fi <<" " <<pr.se <<endl;
                return ;
            }
        }
        cout <<"No" <<endl;
    }
}

int main()
{
#ifdef yukihana0416
freopen("in.txt", "r", stdin);
//freopen("out.txt", "w", stdout);
#endif // yukihana0416
    reader.open_alter(1 << 24);

    int tc = 1;
    reader >> tc;
    for(int ca = 1; ca <= tc; ca++)
    {
//        printf("Case #%d: ", ca);
//        printf("Case #%d:\n", ca);
        work();
    }
    return 0;
}