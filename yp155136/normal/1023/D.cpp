#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cassert>
#include <iomanip>
#include <bitset>
using namespace std;

typedef long long      LL;
typedef long double    ld;
typedef pair<int,int>  pii;
typedef pair<LL,LL>    pLL;
typedef vector<int>    vint;
typedef vector<LL>     vLL;
typedef vector<pii>    vpii;
typedef vector<pLL>    vpLL;

#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define F first
#define S second
#define MP make_pair
#define PB push_back

#define Si(x) scanf("%d",&(x));
#define Sii(x,y) scanf("%d %d",&(x),&(y));
#define Siii(x,y,z) scanf("%d %d %d",&(x),&(y),&(z));
#define Siiii(x,y,z,w) scanf("%d %d %d %d",&(x),&(y),&(z),&(w));
#define Siiiii(x,y,z,w,a) scanf("%d %d %d %d %d",&(x),&(y),&(z),&(w),&(a));
#define Siiiiii(x,y,z,w,a,b) scanf("%d %d %d %d %d %d",&(x),&(y),&(z),&(w),&(a),&(b));
#define SL(x) scanf("%lld",&(x));
#define SLL(x,y) scanf("%lld %lld",&(x),&(y));
#define SLLL(x,y,z) scanf("%lld %lld %lld",&(x),&(y),&(z));
#define SLLLL(x,y,z,w) scanf("%lld %lld %lld %lld",&(x),&(y),&(z),&(w));
#define SLLLLL(x,y,z,w,a) scanf("%lld %lld %lld %lld %lld",&(x),&(y),&(z),&(w),&(a));
#define SLLLLLL(x,y,z,w,a,b) scanf("%lld %lld %lld %lld %lld %lld",&(x),&(y),&(z),&(w),&(a),&(b));

#define Pi(x) printf("%d\n",(x));
#define Pii(x,y) printf("%d %d\n",(x),(y));
#define Piii(x,y,z) printf("%d %d %d\n",(x),(y),(z));
#define Piiii(x,y,z,w) printf("%d %d %d %d\n",(x),(y),(z),(w));
#define Piiiii(a,b,c,d,e) printf("%d %d %d %d %d\n",(a),(b),(c),(d),(e));
#define Piiiiii(a,b,c,d,e,f) printf("%d %d %d %d %d %d\n",(a),(b),(c),(d),(e),(f));
#define PL(x) printf("%lld\n",(x)*1LL);
#define PLL(x,y) printf("%lld %lld\n",(x)*1LL,(y)*1LL);
#define PLLL(x,y,z) printf("%lld %lld %lld\n",(x)*1LL,(y)*1LL,(z)*1LL);
#define PLLLL(x,y,z,w) printf("%lld %lld %lld %lld\n",(x)*1LL,(y)*1LL,(z)*1LL,(w)*1LL);
#define PLLLLL(a,b,c,d,e) printf("%lld %lld %lld %lld %lld\n",(a)*1LL,(b)*1LL,(c)*1LL,(d)*1LL,(e)*1LL);
#define PLLLLLL(a,b,c,d,e,f) printf("%lld %lld %lld %lld %lld %lld\n",(a)*1LL,(b)*1LL,(c)*1LL,(d)*1LL,(e)*1LL,(f)*1LL);

#define Pi1(x) printf("%d",  (x));
#define PL1(x) printf("%lld",(x));
#define Pspace putchar(' ');
#define Pendl  puts("");

#define MEM0(x) memset( (x), 0, sizeof( (x) ) )
#define MEM1(x) memset( (x),-1, sizeof( (x) ) )
#define REP1(i,n)  for (int i = 1; (n) >= i ; ++i)
#define REP0(i,n)  for (int i = 0; (n) >  i ; ++i)

#define IOS ios::sync_with_stdio(0); cin.tie(0);

int myRnd() {
    return abs(  ((rand()<<15) ^ rand()) );
}

int myRnd(int L,int R) {
    return abs(( (rand()<<15)^rand() ) ) % (R-L+1) + L;
}

void Parr(int *arr,int L,int R) {
    for (int i=L;R>=i;i++) {
        printf("%d%c",arr[i]," \n"[i==R]);
    }
}

void Pvec(vint v) {
    for (int i=0;SZ(v)>i;i++) {
        printf("%d%c",v[i]," \n"[i==SZ(v)-1]);
    }
}

void Sarr(int *arr,int L,int R) {
    for (int i=L;R>=i;i++)
    {
        Si(arr[i]);
    }
}

const int N = 2e5 + 6;
const int INF = 0x3f3f3f3f;
const int mod = 1000000000 + 7;

int a[N];

struct Node
{
    Node *lc,*rc;
    int mn;
    Node():lc(NULL),rc(NULL),mn(INF){}
    void pull()
    {
        mn = min(lc->mn,rc->mn);
    }
};

Node* Build(int L,int R)
{
    Node* node = new Node();
    if(L == R)
    {
        node->mn = a[L];
        return node;
    }
    int mid=(L+R)>>1;
    node->lc = Build(L,mid);
    node->rc = Build(mid+1,R);
    node->pull();
    return node;
}

int query(Node* node,int L,int R,int l,int r)
{
    if (l>R || L>r) return INF;
    else if(l<=L && R<=r) return node->mn;
    int mid=(L+R)>>1;
    return min(query(node->lc,L,mid,l,r) , query(node->rc,mid+1,R,l,r));
}

vector<int> v[N];

bool judge(int n,int q,bool have_0,int pos_0)
{
    Node* root = Build(1,n);
    REP1(i,n)
    {
        v[ a[i] ].push_back(i);
    }
    REP1(i,q)
    {
        if (SZ(v[i]))
        {
            if (query(root,1,n,v[i].front(),v[i].back()) < i) return false;
        }
    }
    if (SZ(v[q]) == 0 && !have_0) return false;
    else if (SZ(v[q]) == 0)
    {
        a[ pos_0 ] = q;
        return true;
    }
    return true;
}

int main () {
    srand(time(NULL));
    int n,q;
    Sii(n,q);
    Sarr(a,1,n);
    bool have_0 = false;
    int pos_0=-1;
    REP1(i,n)
    {
        if (a[i] == 0) have_0 = true,pos_0 = i;
    }
    REP1(i,n)
    {
        if (a[i] == 0)
        {
            if (i > 1 && a[i-1] != 0) a[i] = a[i-1];
            else if (i<n && a[i+1] != 0) a[i] = a[i+1];
        }
    }
    for (int i=n;i>=1;i--)
    {
        if (a[i] == 0)
        {
            if (i > 1 && a[i-1] != 0) a[i] = a[i-1];
            else if (i<n && a[i+1] != 0) a[i] = a[i+1];
        }
    }
    REP1(i,n)
    {
        if (a[i] == 0)
        {
            if (i > 1 && a[i-1] != 0) a[i] = a[i-1];
            else if (i<n && a[i+1] != 0) a[i] = a[i+1];
        }
    }
    for (int i=n;i>=1;i--)
    {
        if (a[i] == 0)
        {
            if (i > 1 && a[i-1] != 0) a[i] = a[i-1];
            else if (i<n && a[i+1] != 0) a[i] = a[i+1];
        }
    }
    if (a[1] == 0)
    {
        REP1(i,n)
        {
            a[i] = q;
        }
    }
    if (judge(n,q,have_0,pos_0))
    {
        puts("YES");
        Parr(a,1,n);
    }
    else
    {
        puts("NO");
    }
}