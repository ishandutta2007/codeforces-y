#include<bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < int(n); ++i)
#define rrep(i,n) for (int i = int(n)-1; i >= 0; i--)
#define rep2(i,s,n) for (int i = int(s); i < int(n); ++i)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vd vector<double>
#define vs vector<string>
#define vc vector<char>
#define vb vector<bool>
#define vp vector<P>
using namespace std;
using ll = long long;
using P = pair<int,int>;
using LP = pair<ll,ll>;
template<class S,class T> istream& operator>>(istream &is,pair<S,T> &p) { return is >> p.first >> p.second; }
template<class S,class T> ostream& operator<<(ostream &os,const pair<S,T> &p) { return os<<'{'<<p.first<<","<<p.second<<'}'; }
template<class T> istream& operator>>(istream &is,vector<T> &v) { for(T &t:v){is>>t;} return is; }
template<class T> ostream& operator<<(ostream &os,const vector<T> &v) { os<<'[';rep(i,v.size())os<<v[i]<<(i==int(v.size()-1)?']':','); return os; }
void Yes(bool b) { cout << (b ? "Yes" : "No") << endl; }
void YES(bool b) { cout << (b ? "YES" : "NO") << endl; }
template<class T> bool chmin(T& a,T b) {if(a > b){a = b; return true;} return false;}
template<class T> bool chmax(T& a,T b) {if(a < b){a = b; return true;} return false;}
const int inf = 1001001001;
const ll linf = 1001001001001001001;

int pos[510][510];
vi a;

int rec(int i,int j) {
    if(pos[i][j] != -1) return pos[i][j];
    if(j-i == 1) return pos[i][j] = a[i];
    rep2(k,i+1,j) {
        int l = rec(i,k),r = rec(k,j);
        if(l == 0 or r == 0) continue;
        if(l == r) return pos[i][j] = l+1;
    }
    return pos[i][j] = 0;
}

int dp[510];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    a.resize(n);
    cin >> a;
    rep(i,510) rep(j,510) pos[i][j] = -1;
    rep(i,n) rep2(j,i+1,n+1) {
        if(pos[i][j] == -1) rec(i,j);
    }
    rep(i,510) dp[i] = inf;
    dp[0] = 0;
    rep(i,n) rep2(j,i+1,n+1) {
        if(pos[i][j]) chmin(dp[j],dp[i]+1);
    }
    cout << dp[n] << endl;
}