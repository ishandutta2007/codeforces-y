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
#include <list>
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
typedef pair<LL,LL> pll;
typedef vector<int> vi;

template< typename T >
inline void read(T &res)
{
    T x=0; bool f=0; char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')f=!f; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    res = f ? -x : x ;
}

template< typename T >
inline void Max(T &a, T b) {if(a<b) a=b;}
template< typename T >
inline void Min(T &a, T b) {if(b<a) a=b;}

const double pi=(double) acos(-1.0);
const int MOD=(int) 1e9+7;
const int INF=(int) 0x3f3f3f3f;
const LL  LINF=(LL) INF<<32|INF;
const int SINF=(uint) ~0>>1;
const LL  SLINF=(ULL) (-1)>>1;
const double DINF=(double) 1e50;
const double eps=(double) 1e-8;
const int maxn=(int) 1e5+20;
const int maxm=(int) 1e6+15;

inline int sig(double x) {return x<-eps?-1:x>eps;}
inline void fadd(LL &x,LL a) {x+=a; if(x>=MOD) x-=MOD;}

//--------------start------------------

struct Mat
{
    LL a[2][2];

    inline void init() {memset(this,0,sizeof(Mat));}

    Mat operator * (const Mat &t) const
    {
        Mat res; res.init();
        for(int k=0;k<2;k++)
            for(int i=0;i<2;i++)
                for(int j=0;j<2;j++)
                    res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j])%MOD;
        return res;
    }
};

Mat Mp(Mat a,LL n)
{
    Mat res; res.init();
    res.a[0][0]=res.a[1][1]=1;
    while(n)
    {
        if(n&1) res=res*a;
        a=a*a; n>>=1;
    }
    return res;
}

LL fp(LL a,LL n)
{
    LL res=1;
    while(n)
    {
        if(n&1) res=res*a%MOD;
        a=a*a%MOD; n>>=1;
    }
    return res;
}

LL A,B,x,n;

void work()
{
    while(~scanf("%I64d%I64d%I64d%I64d",&A,&B,&n,&x))
    {
        Mat m;
        m.a[0][0]=1; m.a[0][1]=1;
        m.a[1][0]=0; m.a[1][1]=A;
        m=Mp(m,n+1);
        LL sa=m.a[0][1];
//        cout <<"sa : " <<sa <<endl;
        LL ans=(sa*B)%MOD;
        LL temp=(fp(A,n)*(x-B))%MOD;
        ans+=temp;
        ans=(ans%MOD+MOD)%MOD;
        cout <<ans <<endl;
    }
}


//--------------end--------------------

//#define yukihana0416
int main()
{
#ifdef yukihana0416
freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);
#endif // yukihana0416
    work();
    return 0;
}