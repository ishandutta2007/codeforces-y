#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <set>
#include <map>
#include <cstring>
#include <time.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define Debug(x) cout<<#x<<"="<<x<<endl;
#define For(i,l,r) for(int i=l;i<=r;i++)
#define tr(e,x) for(typeof(x.begin()) e=x.begin();e!=x.end();e++)
#define printTime cout<<"Time:"<<pre-clock()<<endl;pre=clock();
const int inf=~0U>>1,maxn=1000;
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n,m;
int Min[maxn];
int main()
{
    //freopen("in","r",stdin);
    cin>>n;int a,b,c;
    rep(i,n)Min[i]=inf,cin>>c;
    cin>>m;
    rep(i,m)
    {
        cin>>a>>b>>c;--a;--b;
        Min[b]=min(Min[b],c);
    }
    int cnt=0,total=0;
    rep(i,n)if(Min[i]==inf)cnt++;else total+=Min[i];
    if(cnt>1)cout<<-1<<endl;
    else cout<<total<<endl;
}