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

using P = pair<int, int>;

void solve(){
    int n; cin >> n;
    vector<int> c(n), l(n), r(n);
    for(int i = 0; i < n; i++){
        cin >> c[i] >> l[i] >> r[i];
    }
    UnionFind uf(n);
    vector<set<P>> rs(2);
    vector<int> max_index(2, -1);
    vector<P> vp(n);
    for(int i = 0; i < n; i++){
        vp[i] = P(l[i], i);
    }
    sort(vp.begin(), vp.end());
    for(auto [_, idx]: vp){
        int cc = c[idx]^1;
        if(!rs[cc].empty()){
            for(auto [rr, ii]: rs[cc]){
                if(rr >= l[idx]) uf.unionSet(idx, ii);
            }
            P p = *prev(rs[cc].end());
            rs[cc].clear();
            rs[cc].insert(p);
        }
        rs[c[idx]].insert(P(r[idx], idx));
    }
    
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(uf.root(i) == i) ans++;
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