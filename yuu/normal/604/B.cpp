#include <stdio.h>
#include <locale>
#define FOR(i, j, k) for(int i=j; i<=k; i++)
#define DFOR(i, j, k) for(int i=j; i>=k; i--)
template <typename T> inline void read(T &x){
    char c;
    bool nega=0;
    while((!isdigit(c=getchar()))&&(c!='-'));
    if(c=='-'){
        nega=1;
        c=getchar();
    }
    x=c-48;
    while(isdigit(c=getchar()))
        x=x*10+c-48;
    if(nega)
        x=-x;
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
#define taskname "B"
#include <algorithm>
using namespace std;
int s[100000];
int n, k, m;
int main(){
    #ifdef I_have_no_girlfriend
        if(fopen(taskname".inp", "r"))
            freopen(taskname".inp", "r", stdin);
    #endif // I_have_no_girlfriend
    read(n);
    read(k);
    FOR(i, 1, n)
        read(s[i]);
    if(k>n) k=n;
    int ans=0;
    FOR(i, 0, k){
        if(i*2+(k-i)>=n){
            m=i;
            break;
        }
    }
    FOR(i, 2*m+1, n)
        ans=max(ans, s[i]);
    int i=1, j=2*m;
    while(i<j){
        ans=max(ans, s[i]+s[j]);
        i++;
        j--;
    }
    write(ans);
}