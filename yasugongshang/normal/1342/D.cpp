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
int to[N],s[N],c[N],ans;
queue<int> q;
vector<int> v[N];
int main(){
	#ifdef Brollan
		freopen("1.in","r",stdin);
	#endif
	int n=read(),k=read();
	For(i,1,n)to[read()]++;
	Rep(i,k,1)s[i]=s[i+1]+to[i];
	For(i,1,k){
		c[i]=read();
		ans=max(ans,(s[i]+c[i]-1)/c[i]);
	}
	Rep(i,k,1){
		for(int k=1;k<=c[i]-c[i+1]&&q.size()<n;k++)for(int j=1;j<=ans&&q.size()<n;j++)q.push(j);
		For(j,1,to[i]){
			int t=q.front(); q.pop();
			v[t].pb(i);
		}
	}
	writeln(ans);
	For(i,1,ans){
		wri(v[i].size());
		for(auto j:v[i])wri(j); puts("");
	}
}