#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

#define LL long long

#define fi first
#define se second
#define lson l,mid,id<<1
#define rson mid+1,r,id<<1|1
#define ls id<<1
#define rs id<<1|1
#define MID(a,b) (((a)+(b))>>1)
#define maxx(a,b) ((a)<(b)?(b):(a))
#define minx(a,b) ((a)<(b)?(a):(b))
#define absx(a) ((a)<0?-(a):(a))
#define mk(a,b) make_pair(a,b)
#define pb(a) push_back(a)
#define itr iterator
#define lowbit(x) ((x)&-(x))

typedef unsigned LL ULL;
typedef unsigned uint;
typedef map<int,int> mii;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<LL,LL> pLL;

template< typename T > inline void read(T &x) {
    static bool fr_f; static char fr_ch;
    fr_f=0; x=0; fr_ch=getchar();
    while(fr_ch<'0' || '9'<fr_ch) {if(fr_ch=='-') fr_f=1; fr_ch=getchar();}
    while('0'<=fr_ch && fr_ch<='9') {x=(x<<1)+(x<<3)+fr_ch-'0'; fr_ch=getchar();}
    if(fr_f) x=-x;
}

template< typename T > inline void Max (T &a, T b) {if(a<b) a=b;}
template< typename T > inline void Min (T &a, T b) {if(b<a) a=b;}
template< typename T > inline void Swap(T &a, T &b) {T c=a;a=b;b=c;}
template< typename T > inline T Abs(T a) {if(a<0) return -a; else return a;}

const double   pi = acos(-1.0) ;
const int     MOD = (int)1e9+7 ;
const int     INF = (int)0x3f3f3f3f ;
const LL     LINF = (LL)INF<<32|INF ;
const int    SINF = (uint)(-1)>>1 ;
const LL    SLINF = (ULL)(-1)>>1 ;
const double DINF = 1e50 ;
const double  eps = 1e-5 ;
const int    maxn = (int) 2e5+20 ;
const int    maxm = (int) 1e6+20 ;
const int    maxk = (int) 1000+20 ;

inline int sig(double x) {return x<-eps?-1:x>eps;}
inline LL fp(LL a,LL n,LL p) {LL res=1; for(;n;n>>=1,a=a*a%p) if(n&1) res=res*a%p; return res;}
template<typename T>inline T gcd(T a,T b) {for(T c;b;c=a%b,a=b,b=c); return a;}

//--------------------start--------------------

int n,m;
char str[maxn];
vector<char> vec[maxn];


void work()
{
    cin >>n >>m;
    cin >>str;

    for(int i = 0 ; i < n ; i++)
    {
        vec[i % m].pb(str[i]);
    }

    bool ans = 0;
    for(int j = 0; j < m; j++)
    {
        bool check = 0;
        for(int i = 1; i < vec[j].size(); i++)
        {
            if(vec[j][i] == '.')
            {
                if(vec[j][i - 1] == '.')
                {
                    check = 1;
                    vec[j][i] = '1';
                    vec[j][i - 1] = '0';
                }
                else
                {
                    vec[j][i] = vec[j][i - 1] == '0' ? '1' : '0';
                    check = 1;
                }

            }
            else
            {
                if(vec[j][i - 1] == '.')
                {
                    vec[j][i - 1] = vec[j][i] == '0' ? '1' : '0';
                    check = 1;
                }
                else
                {
                    check |= vec[j][i - 1] != vec[j][i];
                }
            }
        }
        if(vec[j][0] == '.') vec[j][0] = '0';
        ans |= check;
    }

    if(ans)
    {
        for(int i = 0; i < n; i++)
        {
            str[i] = vec[i % m][i / m];
        }
        cout <<str <<endl;
    }
    else
    {
        cout <<"No" <<endl;
    }
}

//---------------------end---------------------

int main()
{
#ifdef yukihana0416
freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);
#endif // yukihana0416
    work();
    return 0;
}