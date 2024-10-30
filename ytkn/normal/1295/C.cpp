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
typedef long long ll;

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

void solve(){
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();
    auto nx = vec2d(n+1, 26, n);
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j < 26; j++){
            nx[i][j] = nx[i+1][j];
        }
        nx[i][s[i]-'a'] = i;
    }
    int idx = 0;
    int pos = 0;
    int ans = 0;
    while(idx < m){
        int x = t[idx]-'a';
        if(nx[0][x] == n) {
            cout << -1 << endl;
            return;
        }
        if(nx[pos][x] == n){
            pos = 0;
        }else{
            if(pos == 0) ans++;
            pos = nx[pos][x]+1;
            idx++;
        }
    }
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(10) << fixed;
    int t; cin >> t;
    while(t--) solve();
}