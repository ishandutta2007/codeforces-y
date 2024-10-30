//
// Created by yamunaku on 2020/03/04.
//

#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < (n); i++)
#define repl(i, l, r) for(int i = (l); i < (r); i++)
#define per(i, n) for(int i = ((n)-1); i >= 0; i--)
#define perl(i, l, r) for(int i = ((r)-1); i >= (l); i--)
#define all(x) (x).begin(),(x).end()
#define MOD9 998244353
#define MOD1 1000000007
#define IINF 1000000000
#define LINF 1000000000000000000
#define SP <<" "<<
#define CYES cout<<"Yes"<<endl
#define CNO cout<<"No"<<endl
#define CFS cin.tie(0);ios::sync_with_stdio(false)
#define CST(x) cout<<fixed<<setprecision(x)

using ll = long long;
using ld = long double;
using vi = vector<int>;
using mti = vector<vector<int>>;
using vl = vector<ll>;
using mtl = vector<vector<ll>>;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
template<typename T>
using heap = priority_queue<T, vector<T>, function<bool(const T, const T)>>;

int main(){
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    int a;
    int idxa = -1, idxb = -1;
    rep(i, n){
        scanf("%d", &a);
        if(a % p != 0 && idxa == -1){
            idxa = i;
        }
    }
    rep(i, m){
        scanf("%d", &a);
        if(a % p != 0 && idxb == -1){
            idxb = i;
        }
    }
    cout << idxa + idxb << endl;
    return 0;
}