#include<bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define rrep(i,n) for (int i = (n)-1; i >= 0; i--)
#define rep2(i,s,n) for (int i = (s); i < (n); ++i)
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
template<class T> ostream& operator<<(ostream &os,const vector<T> &v) { os<<'[';rep(i,v.size())os<<v[i]<<(i==v.size()-1?']':','); return os; }
void Yes(bool b) { cout << (b ? "Yes" : "No") << endl; }
void YES(bool b) { cout << (b ? "YES" : "NO") << endl; }
template<class T> bool chmin(T& a,T b) {if(a > b){a = b; return true;} return false;}
template<class T> bool chmax(T& a,T b) {if(a < b){a = b; return true;} return false;}
const int inf = 1001001001;
const ll linf = 1001001001001001001;

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    vi v(n+1);
    rep(i,n) v[a[i]]++;
    set<int> st;
    rep(i,n+1) if(v[i] == 0) st.insert(i);
    vi ans;
    auto del = [&](int x) {
        v[x]--;
        if(v[x] == 0) st.insert(x);
    };
    auto add = [&](int x) {
        if(v[x] == 0) st.erase(x);
        v[x]++;
    };
    while(true) {
        if(*st.begin() < n) {
            int s = *st.begin();
            ans.pb(s);
            del(a[s]);
            add(s);
            a[s] = s;
        } else {
            bool ok = true;
            rep(i,n) if(a[i] != i) {
                ans.pb(i);
                del(a[i]);
                add(n);
                a[i] = n;
                ok = false;
                break;
            }
            if(ok) break;
        }
    }
    cout << ans.size() << '\n';
    for(int i : ans) cout << i+1 << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin >> t;
    rep(i,t) solve();
}