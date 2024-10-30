#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pb push_back
#define reset(a,b) memset(a,b,sizeof a);
#define ALL(x) x.begin(),x.end()
 
template <typename T>
void cetak(T t){cout << t << ')' << endl;}
template <typename T, typename... V>
void cetak(T t, V... v) {cout << t; if (sizeof...(v)) cout << ", "; cetak(v...);}
 
#define debug(x...) cout << '(' << #x << ") = ("; cetak(x) 
#define sz(x) (int)(x.size())
#define lt(x) (int)(x.length())
typedef int (*func)(int, int);


const int MOD = 1e9 + 7;

int add(int x, int y){
    int ret = x + y;
    if(ret >= MOD) ret -= MOD;
    return ret;
}
int sub(int x, int y){
    int ret = x - y;
    if(ret < 0) ret += MOD;
    return ret;
}
int mul(int x, int y){
    return (long long)x * y % MOD;
}


const int mx = 1e5 + 10;

int val(int i, int j, int n, int m){
    if(i == 0 && j == 0) return 2;
    if(i == 0 && j == m - 1) return 2;
    if(i == n - 1 && j == 0) return 2;
    if(i == n - 1 && j == m - 1) return 2;
    if(i == n - 1) return 3;
    if(i == 0) return 3;
    if(j == m - 1) return 3;
    if(j == 0) return 3;
    return 4;
}

void solve(int tc){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(auto &i : a) for(int &j : i) cin >> j;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(val(i, j, n, m) < a[i][j]){
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << val(i, j, n, m) << ' ';
        }
        cout << '\n';
    }
    
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    int tc = 0;
    while(t--){
        solve(++tc);
    }
}