#include <bits/stdc++.h>
#define sz(v)   ((int)(v).size())
#define  all(v)    ((v).begin()),((v).end())
#define  allr(v)    ((v).rbegin()),((v).rend())
#define   pb         push_back
#define   mp         make_pair
#define   Y            imag()
#define   X            real()
#define    clr(v,d)      memset( v, d ,sizeof(v))
#define   angle(n)      atan2((n.imag()),(n.real()))
#define   vec(a,b)       ((b)-(a))
#define   length(a)      hypot( (a.imag()),(a.real()) )
#define   normalize(a)      (a)/(length(a))
#define    dp(a,b)          (((conj(a))*(b)).real())
#define    cp(a,b)          (((conj(a))*(b)).imag())
#define    lengthsqrt(a)       dp(a,a)
#define    rotate0( a,ang)    ((a)*exp( point(0,ang) ))
#define    rotateA(about,p,ang)   (rotate0(vec(about,p),ang)+about)
#define    lcm(a,b)                ((a*b)/(__gcd(a,b)))
#define    reflection0(m,v)         (conj((v)/(m))*(m))
#define     reflectionA(m,v,p0)     (conj( (vec(p0,v))/(vec(p0,m)) ) * (vec(p0,m)) ) + p0
#define     same(p1,p2)               ( dp(  vec(p1,p2),vec(p1,p2)) < eps )
#define     point                    complex<long double>
#define     PI                       acos(-1)
typedef  long long     ll ;
typedef  unsigned long long ull;
const double eps= (1e-15);
using namespace std;
int dcmp(double a,double b){   return fabs(a-b)<=eps ? 0: (a>b)? 1:-1  ;}
int getBit(ll num, int idx) {return ((num >> idx) & 1ll) == 1;}
int setBit1(int num, int idx) {return num | (1<<idx);}
ll setBit0(ll num, int idx) {return num & ~(1ll<<idx);}
ll flipBit(ll num, int idx) {return num ^ (1ll<<idx);}
void GO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
int countNumBit1(int mask) {int ret=0; while (mask) 	{mask &= (mask-1);++ret;	}return ret;}
const ll N=200000+5,mod=998244353,sh=1000000,inf=100000000;
vector<int> v;
int vis[N];
int main(){
    GO();
    int T=1;
    cin>>T;
    while(T--){
        int n,k,m;
        cin>>n>>k>>m;
        v.clear();
        for(int i=1;i<=n;i++) vis[i]=0;
        for(int i=0;i<m;i++){
            int no;
            cin>>no;
            vis[no]=1;
        }
        for(int i=1;i<=n;i++){
            if(vis[i]==0){
                v.pb(i);
            }
        }
        int cnt=sz(v);
        if(cnt==0){
            cout<<"YES\n";
            continue;
        }
        while(cnt>=k){

            cnt-=k;
            cnt++;
        }
        if(k-cnt>1){
            cout<<"NO\n";
            continue;
        }
        bool ok=0;
        for(int i=2;i<n;i++){
            if(vis[i]==0) continue;
            auto it=upper_bound(all(v),i);
            int aft=v.end()-it;
            int bef= it-v.begin();
            if(aft>=k/2&&bef>=k/2){
                ok=1;
            }
        }
        if(ok==1) cout<<"YES\n";
        else
            cout<<"NO\n";

    }
}