#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define eb emplace_back
typedef long long ll;
typedef pair<int, int> pi;

int n;
const int maxn = 105;

int c[maxn], b[maxn];

ll pb[maxn], ppb[maxn]; 
ll dp[maxn][maxn * maxn];
ll pre[maxn][maxn * maxn];
ll S;
const int mod = 1e9 + 7;

void add(ll &a, ll b){
    a += b;
    if(a >= mod)
        a -= mod;
}

ll get(ll x){
    dp[0][0] = 1;
    for(int i = 0;i < n;i++){
        for(int j = 0;j <= S;j++){
            pre[i][j] = dp[i][j];
            if(j > 0)
                add(pre[i][j], pre[i][j-1]);
        }
        ll lb = x * (i + 1) + ppb[i];
        for(ll j = max(0LL, lb);j <= S;j++){
            ll l = max(x * i + ((i > 0) ? ppb[i-1] : 0), 1LL * j - c[i+1]);  
            ll tmp;
            if(l <= j)
                tmp = (pre[i][j] - ((l > 0) ? pre[i][l-1] : 0) + mod) % mod; 
            else
                tmp = 0;
            add(dp[i+1][j], tmp); 
        }
    }
    ll ans = 0;
    for(int j = 0;j <= S;j++){
        add(ans, dp[n][j]);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    S = 0;
    c[0] = 0;
    for(int i = 1;i <= n;i++){
        cin >> c[i];
        S += c[i];
    }
    b[0] = 0;
    pb[0] = 0;
    ppb[0] = 0;
    for(int i = 1;i < n;i++){
        cin >> b[i];
        pb[i] = pb[i-1] + b[i];
        ppb[i] = ppb[i-1] + pb[i];
    }
    int Q;
    cin >> Q;
    ll x;
    cin >> x;
    cout << get(x) << endl;
    return 0;
}