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

struct UnionFind {
    vector<int> data;
    UnionFind(int size) : data(size, -1) {}
    bool unionSet(int x, int y) {
        x = root(x); y = root(y);
        if (x != y) {
        if (data[y] < data[x]) swap(x, y);
        data[x] += data[y]; data[y] = x;
        }
        return x != y;
    }
    bool findSet(int x, int y) {
        return root(x) == root(y);
    }
    int root(int x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
    int size(int x) {
        return -data[root(x)];
    }
};

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    vector<vector<int>> indices(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; a[i]--;
        indices[a[i]].push_back(i);
    }
    int ans = 0;
    vector<int> cnt(n);
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    for(int l = 0; l < n; l++){
        int mx = 0;
        cnt.assign(n, 0);
        for(int r = l; r <= n; r++){
            if((r-l)%2 == 0 && mx*2 <= r-l){
                if(r == n){
                    // cout << "[" << l << ", " << r << ")" << endl;
                    if(dp[l] != -1) chmax(dp[r], dp[l]);
                }else if(l == 0){
                    // cout << "[" << l << ", " << r << ")" << endl;
                    chmax(dp[r+1], dp[l]+1);
                }else if(a[l-1] == a[r]){
                    // cout << "[" << l << ", " << r << ")" << endl;
                    if(dp[l] != -1)  chmax(dp[r+1], dp[l]+1);
                }
            }
            if(r == n) break;
            cnt[a[r]]++;
            chmax(mx, cnt[a[r]]);
        }
    }
    // print_vector(dp);
    cout << dp[n] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(10) << fixed;
    int t; cin >> t;
    while(t--) solve();
}