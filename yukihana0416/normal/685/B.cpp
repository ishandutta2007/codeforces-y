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
const int maxn=(int) 300000+20;
const int maxm=(int) 1000000+15;

inline int sig(double x) {return x<-eps?-1:x>eps;}

//--------------start------------------


int n,m;
vi G[maxn];
int f[maxn],hson[maxn];
int sz[maxn];
int ans[maxn];

void dfs(int u,int fa)
{
    ans[u]=u;
    hson[u]=0;
    f[u]=fa;
    sz[u]=1;
    int k=G[u].size();
    for(int i=0;i<k;i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(!hson[u] || sz[v]>sz[hson[u]]) hson[u]=v;
    }

    if(!hson[u]) return ;
    int temp=ans[hson[u]];
    while(temp!=u && sz[u]>=2*sz[temp])
    {
//        cout <<u <<" " <<temp <<endl;
        if(f[temp]==0) break;
        temp=f[temp];
    }
    ans[u]=temp;
//    cout <<u <<" " <<ans[u] <<endl;
}



void work()
{
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=2;i<=n;i++)
        {
            int x; read(x);
            G[x].pb(i); G[i].pb(x);
        }

        dfs(1,0);

        while(m--)
        {
            int x; read(x);
            printf("%d\n",ans[x]);
        }
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