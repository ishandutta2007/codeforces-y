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

class Scc{
    public:
        int N;
        vector<vector<int>> G;
        vector<vector<int>> G_inv;
        vector<int> idx;

        Scc(int n){
            N = n;
            G = vector<vector<int>>(n, vector<int>());
            G_inv = vector<vector<int>>(n, vector<int>());
            used = vector<bool>(n, false);
            idx = vector<int>(n);
        }

        void add_edge(int from, int to){
            G[from].push_back(to);
            G_inv[to].push_back(from);
        }

        vector<vector<int>> scc(){
            vector<vector<int>> ans;
            for(int i = 0; i < N; i++){
                if(!used[i]) dfs1(i);
            }
            clear();
            int cur = 0;
            for(int i = vs.size()-1; i >= 0; i--){
                if(!used[vs[i]]) {
                    dfs2(vs[i], cur);
                    cur++;
                    ans.push_back(buf);
                    buf.clear();
                }
            }
            return ans;
        }

    private:
        vector<bool> used;
        vector<int> vs;
        vector<int> buf;
        void clear(){
            for(int i = 0; i < N; i++) used[i] = false;
        }

        void dfs1(int v){
            used[v] = true;
            for(int i = 0; i < G[v].size(); i++){
                if(!used[G[v][i]]) dfs1(G[v][i]);
            }
            vs.push_back(v);
        }

        void dfs2(int v, int k){
            used[v] = true;
            idx[v] = k;
            for(int i = 0; i < G_inv[v].size(); i++){
                if(!used[G_inv[v][i]]) dfs2(G_inv[v][i], k);
            }
            buf.push_back(v);
        }
};

void solve(){
    int n, m; cin >> n >> m;
    Scc scc(n);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        scc.add_edge(a, b);
    }
    auto v = scc.scc();
    if(v.size() == 1){
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    int p = v[0].size();
    int j = n-p;
    cout << j << ' ' << p << endl;
    for(int i = 1; i < v.size(); i++){
        for(int x: v[i]) cout << x+1 << ' ';
    }
    cout << endl;
    for(int x: v[0]) cout << x+1 << ' ';
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(10) << fixed;
    int t; cin >> t;
    while(t--) solve();
}