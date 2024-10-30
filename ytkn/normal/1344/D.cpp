#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <tuple>
#include <cmath>
#include <numeric>
#include <functional>
#include <cassert>

#define debug_value(x) cerr << "line" << __LINE__ << ":<" << __func__ << ">:" << #x << "=" << x << endl;
#define debug(x) cerr << "line" << __LINE__ << ":<" << __func__ << ">:" << x << endl;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

using namespace std;

template<typename T>
vector<vector<T>> vec2d(int n, int m, T v){
    return vector<vector<T>>(n, vector<T>(m, v));
}

template<typename T>
vector<vector<vector<T>>> vec3d(int n, int m, int k, T v){
    return vector<vector<vector<T>>>(n, vector<vector<T>>(m, vector<T>(k, v)));
}

template<typename T>
void print_vector(vector<T> v, char delimiter=' '){
    if(v.empty()) {
        cout << endl;
        return;
    }
    for(int i = 0; i+1 < v.size(); i++) cout << v[i] << delimiter;
    cout << v.back() << endl;
}


/**
 * thanks to
 * https://kenkoooo.hatenablog.com/entry/2016/11/30/163533
 */
__int128 parse(string &s) {
  __int128 ret = 0;
  for (int i = 0; i < s.length(); i++)
    if ('0' <= s[i] && s[i] <= '9')
      ret = 10 * ret + s[i] - '0';
  return ret;
}

istream & operator >> (istream &in,  __int128_t &m){
    string s; cin >> s;
    m = parse(s);
    return in;
}


ostream &operator<<(std::ostream &dest, __int128_t value) {
    ostream::sentry s(dest);
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = end(buffer);
        do {
        --d;
        *d = "0123456789"[tmp % 10];
        tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
        --d;
        *d = '-';
        }
        int len = end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
        dest.setstate(ios_base::badbit);
        }
    }
    return dest;
}

using ll = long long;
const ll inf = 4e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(10) << fixed;
    int n; ll k; cin >> n >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    auto f = [&](ll x){
        return 3*x*x-3*x+1;
    };
    auto count_ge_elm = [&](int i, ll v) -> ll{
        if(a[i]-f(1) < v) return 0; 
        if(a[i]-f(a[i]) >= v) return a[i];
        ll l = 1, r = a[i];
        while(r-l > 1){
            ll x = (l+r)/2;
            if(a[i]-f(x) >= v) l = x;
            else r = x;
        }
        return l;
    };
    auto count_ge = [&](ll v)->ll{
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ans += count_ge_elm(i, v);
        }
        return ans;
    };
    ll l = -inf, r = inf;
    while(r-l > 1){
        ll v = (l+r)/2;
        if(count_ge(v) >= k) l = v;
        else r = v;
    }
    ll rem = k-count_ge(l+1);
    for(int i = 0; i < n; i++){
        ll ans = count_ge_elm(i, l+1);
        ll possible = count_ge_elm(i, l)-ans;
        ll add = min(rem, possible);
        ans += add;
        rem -= add;
        cout << ans << ' ';
    }
    cout << endl;
}