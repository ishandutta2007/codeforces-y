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
    int n; cin >> n;
    vector<bool> ok_go(n, false), ok_back(n, false);
    for(int i = 0; i < n; i++){
        int a; cin >> a; a--;
        if(a == -1) ok_go[i] = true;
        else ok_back[i] = true;
    }
    if(ok_go[n-1]){
        for(int i = 1; i <= n+1; i++) cout << i << ' ';
        cout << endl;
        return;
    }
    if(ok_back[0]){
        cout << n+1 << ' ';
        for(int i = 1; i <= n; i++) cout << i << ' ';
        cout << endl;
        return;
    }
    for(int i = 0; i+1 < n; i++){
        if(ok_go[i] && ok_back[i+1]){
            for(int j = 1; j <= i+1; j++) cout << j << ' ';
            cout << n+1 << ' ';
            for(int j = i+2; j <= n; j++) cout << j << ' ';
            cout << endl;
            return;
        }
    }
    if(ok_go[n-1] && ok_back[0]){
        cout << n << ' ' << n+1 << ' ';
        for(int i = 1; i <= n-1; i++) cout << i << ' ';
        cout << endl;
        return;
    }
    cout << -1 << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(10) << fixed;
    int t; cin >> t;
    while(t--) solve();
}