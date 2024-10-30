#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define mp make_pair
#define PI pair<ll,ll>
#define poly vector<ll>
#define mem(a) memset((a),0,sizeof(a))
#define For(i,l,r) for(int i=(int)(l);i<=(int)(r);i++)
#define Rep(i,r,l) for(int i=(int)(r);i>=(int)(l);i--)
#define pb push_back
#define fi first
#define se second
#define SZ(x) ((int)(x.size()))
inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline ll read(){
	ll x = 0; char ch = gc(); bool positive = 1;
	for (; !isdigit(ch); ch = gc())	if (ch == '-')	positive = 0;
	for (; isdigit(ch); ch = gc())	x = x * 10 + ch - '0';
	return positive ? x : -x;
}
inline void write(ll a){
    if(a<0){
    	a=-a; putchar('-');
	}
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writeln(ll a){write(a); puts("");}
inline void wri(ll a){write(a); putchar(' ');}
ll rnd(){
	ull ans=0;
	For(i,0,4)ans=ans<<15^rand();
	return ans%((ull)1<<63);
}
const int N=200005;
vector<int> v[N];
int n,a[N],dep[N],sum[2],ans[2];

void dfs(int p,int fa){
	dep[p]=dep[fa]^1;
	for(auto i:v[p])if(i!=fa){
		dfs(i,p);
	}
	ans[dep[p]]++;
	//sum[dep[p]]+=a[p];
}
int main(){
	#ifdef Brollan
		freopen("1.in","r",stdin);
	#endif
	n=read();
	For(i,1,n-1){
		int s=read(),t=read();
		v[s].pb(t); v[t].pb(s);
	}
	For(i,1,n)if(v[i].size()>=2){
		dfs(i,0); 
		cout<<min(sum[0]+ans[1]-1,sum[1]+ans[0]-1)<<endl;
		//cout<<ans[0]<<" "<<ans[1]<<endl;
		return 0;
	}
}
/*
49 49,1

a,a
2a,a
3a,a
6a,a
7a,a
14a,a
a,b,3->a-b,b,1/a+a,b-a,2
a,b,2->a,b+a,3/a,b+b+a,3
a,b,1->a,b+b,3
*/