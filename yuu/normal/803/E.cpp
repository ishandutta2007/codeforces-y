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
int n, k;
string s;
bool f[1001][2003];
int trace[1001][2003];
const int zero=1001;
void output(int n, int x){
    if(n==0) return;
    output(n-1, trace[n][x]);
    if(trace[n][x]<x) putchar('W');
    else if(trace[n][x]>x) putchar('L');
    else putchar('D');
}
int main(){
    #ifdef Uiharu
        if(fopen(taskname".in", "r"))
            freopen(taskname".in", "r", stdin);
    #endif // Uiharu
    cin>>n>>k>>s;
    f[0][zero]=1;
    FFOR(i, 0, n){
        if(s[i]=='W'){
            FOR(x, -k+1, k-1) if(f[i][zero+x]){
                f[i+1][zero+x+1]=f[i][zero+x];
                trace[i+1][zero+x+1]=zero+x;
            }
        }
        else if(s[i]=='L'){
            FOR(x, -k+1, k-1) if(f[i][zero+x]){
                f[i+1][zero+x-1]=f[i][zero+x];
                trace[i+1][zero+x-1]=zero+x;
            }
        }
        else if(s[i]=='D'){
            FOR(x, -k+1, k-1) if(f[i][zero+x]){
                f[i+1][zero+x]=f[i][zero+x];
                trace[i+1][zero+x]=zero+x;
            }
        }
        else{
            FOR(x, -k+1, k-1) if(f[i][zero+x]){
                f[i+1][zero+x+1]=f[i][zero+x];
                trace[i+1][zero+x+1]=zero+x;
                f[i+1][zero+x-1]=f[i][zero+x];
                trace[i+1][zero+x-1]=zero+x;
                f[i+1][zero+x]=f[i][zero+x];
                trace[i+1][zero+x]=zero+x;
            }
        }
    }
    if(f[n][zero+k]) output(n, zero+k);
    else if(f[n][zero-k]) output(n, zero-k);
    else puts("NO");
}