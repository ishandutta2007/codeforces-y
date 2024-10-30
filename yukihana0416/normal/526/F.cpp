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

#define LL __int64

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
    while(fr_ch<'0' || fr_ch>'9') {if(fr_ch=='-') fr_f=1; fr_ch=getchar();}
    while(fr_ch>='0' && fr_ch<='9') {x=(x<<1)+(x<<3)+fr_ch-'0'; fr_ch=getchar();}
    if(fr_f) x=-x;
}

template< typename T > inline void Max(T &a, T b) {if(a<b) a=b;}
template< typename T > inline void Min(T &a, T b) {if(b<a) a=b;}
template< typename T > inline T Abs(T a) {if(a<0) return -a; else return a;}

const double pi   =    acos(-1.0) ;
const int MOD     = (int)1e9+7 ;
const int INF     = (int)0x3f3f3f3f ;
const LL  LINF    = (LL)INF<<32|INF ;
const int SINF    = (uint)(-1)>>1 ;
const LL  SLINF   = (ULL)(-1)>>1 ;
const double DINF = 1e50 ;
const double eps  = 1e-8 ;
const int maxn    = (int) 3e5+20 ;
const int maxm    = (int) 25000+20 ;
const int maxk    = (int) 1000+20 ;

inline int sig(double x) {return x<-eps?-1:x>eps;}
inline LL fp(LL a,LL n,LL p) {LL res=1; for(;n;n>>=1,a=a*a%p) if(n&1) res=res*a%p; return res;}
template<typename T>inline T gcd(T a,T b) {for(T c;b;c=a%b,a=b,b=c); return a;}

//--------------------start--------------------

int n;
int a[maxn];

struct Node
{
    int f,mn,cnt;
}T[maxn<<2];

Node mer(const Node &a,const Node &b)
{
    Node res;
    res.mn=min(a.mn,b.mn);
    res.f=res.cnt=0;
    if(res.mn==a.mn) res.cnt+=a.cnt;
    if(res.mn==b.mn) res.cnt+=b.cnt;
    return res;
}

inline void lazy(int id)
{
    if(T[id].f)
    {
        T[ls].f+=T[id].f;
        T[rs].f+=T[id].f;
        T[ls].mn+=T[id].f;
        T[rs].mn+=T[id].f;
        T[id].f=0;
    }
}

void build(int l,int r,int id)
{
    if(l==r)
    {
        T[id].f=0;
        T[id].cnt=1;
        T[id].mn=l;
        return ;
    }
    int mid=MID(l,r);
    build(lson);
    build(rson);
    T[id]=mer(T[ls],T[rs]);
}

void update(int val,int L,int R,int l,int r,int id)
{
    if(L<=l && r<=R)
    {
        T[id].f+=val;
        T[id].mn+=val;
        return ;
    }
    lazy(id);
    int mid=MID(l,r);
    if(L<=mid) update(val,L,R,lson);
    if(mid<R)  update(val,L,R,rson);
    T[id]=mer(T[ls],T[rs]);
}

#define ROOT 1,n,1

int mns[maxn],mxs[maxn],mntp,mxtp;

void work()
{
    read(n);
    for(int i=1;i<=n;i++)
    {
        int x,y; read(x), read(y);
        a[x]=y;
    }

    build(ROOT);

    LL ans=0;

    mntp=0; mxtp=0;
    mns[0]=mxs[0]=0;

    for(int i=1;i<=n;i++)
    {
        while(mntp && a[mns[mntp]]>a[i])
        {
            update( a[mns[mntp]],mns[mntp-1]+1,mns[mntp],ROOT);
            mntp--;
        }
        while(mxtp && a[mxs[mxtp]]<a[i])
        {
            update(-a[mxs[mxtp]],mxs[mxtp-1]+1,mxs[mxtp],ROOT);
            mxtp--;
        }
        update(-a[i],mns[mntp]+1,i,ROOT);
        update( a[i],mxs[mxtp]+1,i,ROOT);

        mns[++mntp]=i;
        mxs[++mxtp]=i;

        ans+=T[1].cnt;
    }

    printf("%I64d\n",ans);

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