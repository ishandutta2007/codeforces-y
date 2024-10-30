#include <bits/stdc++.h>
using namespace std;
#define FOR(i, j, k) for(int i=(j); i<=(k); i++)
#define FFOR(i, j, k) for(int i=(j); i<(k); i++)
#define DFOR(i, j, k) for(int i=(j); i>=(k); i--)
#define bug(x) cerr<<#x<<" = "<<(x)<<'\n'
#define pb push_back
#define mp make_pair
#define setbit(s, i) (s|=(1LL<<(i)))
#define bit(s, i) (((s)>>(i))&1LL)
#define mask(i) ((1LL<<(i)))
#define builtin_popcount __builtin_popcountll
using ll=long long;
using ld=long double;
template <typename T> inline void read(T &x){
    char c;
    bool nega=0;
    while((!isdigit(c=getchar()))&&(c!='-'));
    if(c=='-'){
        nega=1;
        c=getchar();
    }
    x=c-48;
    while(isdigit(c=getchar())) x=x*10+c-48;
    if(nega) x=-x;
}
template <typename T> inline void writep(T x){
    if(x>9) writep(x/10);
    putchar(x%10+48);
}
template <typename T> inline void write(T x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    writep(x);
}
template <typename T> inline void writeln(T x){
    write(x);
    putchar('\n');
}
#define taskname "G"
const ll base=1000000007;
ll f[2000001];
ll g[2000001];
int p[2000001];
int n, k;
ll ans;
ll power(ll a, ll b){
    if(b==0) return 1;
    ll t=power(a, b/2);
    t=(t*t)%base;
    if(b%2) t=(t*a)%base;
    return t;
}
vector <pair <int, int> > primes;
vector <int> divisors;
void generate_divisors(int u, int v, int s){
    if(u==primes.size()){
        if(s!=1) divisors.pb(s);
    }
    else{
        generate_divisors(u+1, 0, s);
        if(v<primes[u].second) generate_divisors(u, v+1, s*primes[u].first);
    }
}
int main(){
    #ifdef Uiharu
        if(fopen(taskname".in", "r"))
            freopen(taskname".in", "r", stdin);
    #endif // Uiharu
    read(n);
    read(k);
    FOR(i, 2, k) if(!p[i]) for(int j=i; j<=k; j+=i) if(!p[j]) p[j]=i;
    f[1]=1;
    FOR(i, 2, k){
        primes.clear();
        divisors.clear();
        {
            int u=i;
            while(u>1){
                primes.pb(mp(p[u], 0));
                while(u%primes.back().first==0){
                    u/=primes.back().first;
                    primes.back().second++;
                }
            }
        }
        generate_divisors(0, 0, 1);
        g[i]=g[i-1];
        for(int p: divisors){
            g[i]-=f[i/p-1];
            g[i]+=f[i/p];
        }
        g[i]%=base;
        f[i]=(power(i, n)-g[i])%base;
        f[i]=(f[i]+base)%base;
        ans=(ans+(f[i]^i))%base;
    }
    writeln(ans);
}