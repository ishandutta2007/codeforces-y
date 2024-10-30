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
#define taskname "E"
int n;
ld p[18][18];
ld f[18][mask(17)];
bool done[18][mask(17)];
ld F(int u, int m){
    if(done[u][m]) return f[u][m];
    done[u][m]=1;
    if(m==0) return f[u][m]=(u==n);
    if(u!=n){
        FFOR(i, 0, n) if(i!=u) if(bit(m, i)) f[u][m]=max(f[u][m], F(u, m^mask(i))*p[u][i]+F(i, m^mask(u))*p[i][u]);
        f[u][m]=max(f[u][m], F(n, m^mask(u))*p[n][u]);
    }
    else{
        FFOR(i, 0, n) if(bit(m, i)) f[u][m]=max(f[u][m], F(u, m^mask(i))*p[n][i]);
    }
    return f[u][m];
}
int main(){
    #ifdef Uiharu
        if(fopen(taskname".in", "r"))
            freopen(taskname".in", "r", stdin);
    #endif // Uiharu
    read(n);
    n--;
    DFOR(i, n, 0) DFOR(j, n, 0) cin>>p[i][j];
    ld ans=0;
    FOR(i, 0, n) ans=max(ans, F(i, mask(n)-1));
    cout<<setprecision(16)<<fixed<<ans;
}