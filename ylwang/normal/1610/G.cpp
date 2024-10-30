#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mkp make_pair
#define vi vector<int>
#define pii pair<int,int>
#define SZ(x) ((int)x.size())
#define FI(n) FastIO::read(n)
#define FO(n) FastIO::write(n)
#define ull unsigned long long
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i,k,j) for(int i=(k);i>=(j);i--)
#define For(i,k,j) for(int i=(k);i<=(j);i++)
#define Foe(i,u) for(int i=lst[u],v=e[i].v;i;i=e[i].nxt,v=e[i].v)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define Fin(s) freopen(s,"r",stdin)
#define Fout(s) freopen(s,"w",stdout)
#define file(s) Fin(s".in"),Fout(s".out")
#define INF ((1<<30)-1)
//#define int long long
const int P=1e9+7; //
using namespace std;
template<typename T>inline void ckmax(T &a,T b) {(a<b)&&(a=b);}
template<typename T>inline void ckmin(T &a,T b) {(a>b)&&(a=b);}
inline int mul(int a,int b) {return 1ull*a*b%P;}
inline int add(int a,int b) {return a+b>=P?a+b-P:a+b;}
inline int sub(int a,int b) {return a-b>=0?a-b:a-b+P;}
inline void mulmod(int &a,int b) {a=mul(a, b);}
inline void addmod(int &a,int b) {((a+=b)>=P)&&(a-=P);}
inline void submod(int &a,int b) {((a-=b)<0)&&(a+=P);}
inline int ksm(int a,int b) {int ans=1; for(;b;b>>=1) {if(b&1) ans=1ll*ans*a%P;a=1ll*a*a%P;}return ans;}
inline void fprint(const int &x,char c=' ') {fprintf(stderr,"%d%c",x,c);}
inline void fprint(const pii &x,char c='\n') {fprintf(stderr,"%d %d%c",x.first,x.second,c);}
inline void fprint(const int *f,const int &n,char c='\n') {for(int i=1;i<=n;i++) fprint(f[i]); fprintf(stderr,"%c",c);}
inline void fprint(const vector<int> &f,char c='\n') {for(int i=0;i<(int)f.size();i++) fprint(f[i]); fprintf(stderr,"%c",c);}
inline int inv(int a) {return ksm(a,P-2);}
namespace FastIO {
  const int SIZE=1<<16; char buf[SIZE],obuf[SIZE],str[64]; int bi=SIZE,bn=SIZE,opt;
  int read(char *s) {
    while (bn) {for (;bi<bn&&buf[bi]<=' ';bi++);if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}
    int sn=0;while (bn) {for (;bi<bn&&buf[bi]>' ';bi++) s[sn++]=buf[bi];if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}s[sn]=0;return sn;
  }
  bool read(int& x) {if(x)x=0;int bf=0,n=read(str); if(!n) return 0; int i=0; if (str[i]=='-') bf=1,i=1; for(x=0;i<n;i++) x=x*10+str[i]-'0'; if(bf) x=-x; return 1;}
  void write(int x) {
    if(!x) obuf[opt++]='0'; else {if(x<0) obuf[opt++]='-',x=-x;int sn=0; while(x)str[sn++]=x%10+'0',x/=10;for (int i=sn-1;i>=0;i--) obuf[opt++]=str[i];}
    if (opt>=(SIZE>>1)){fwrite(obuf,1,opt,stdout); opt=0;}
  }
  void write(char x) {obuf[opt++]=x;if (opt>=(SIZE>>1)){fwrite(obuf,1,opt,stdout); opt=0;}}
	void Fflush() {if (opt) fwrite(obuf,1,opt,stdout); opt=0;}
};
inline int read() {int x=0; FI(x); return x;}
const int MN=3e5+5;
struct Node {
  int x,y; Node() {} Node(int X,int Y):x(X),y(Y){}
  static const int P1=998244353,P2=1000000007;
  Node operator + (const Node &b) {return Node((x+b.x)%P1,(y+b.y)%P2);}
  Node operator + (const int &b) {return Node((x+b)%P1,(y+b)%P2);}
  Node operator - (const Node &b) {return Node((x-b.x+P1)%P1,(y-b.y+P2)%P2);}
  Node operator - (const int &b) {return Node((x-b+P1)%P1,(y-b+P2)%P2);}
  Node operator * (const Node &b) {return Node(1ll*x*b.x%P1,1ll*y*b.y%P2);}
  Node operator * (const int &b) {return Node(1ll*x*b%P1,1ll*y*b%P2);}
  bool operator == (const Node &b) const {return x==b.x&&y==b.y;}
  void fprint() {fprintf(stderr,"%d %d\n",x,y);}
};
const Node BASE=(Node){131,1331};
int n,nxt[MN],f[MN][20]; Node g[MN][20],pw[MN];
char s[MN]; int stk[MN],top;
void link(int x,int y,int c) {
	f[x][0]=y; For(i,1,19) f[x][i]=f[f[x][i-1]][i-1];
	g[x][0]=Node(c,c); For(i,1,19) g[x][i]=g[x][i-1]+g[f[x][i-1]][i-1]*pw[1<<(i-1)];
}
int fc(int x,int y) {
	foR(i,19,0) if(f[x][i]&&f[y][i]&&g[x][i]==g[y][i]) x=f[x][i],y=f[y][i];
	return g[x][0].x<g[y][0].x;	
}
signed main() {
	#ifndef ONLINE_JUDGE
		freopen("pro.in","r",stdin);
		freopen("pro.out","w",stdout);
	#endif
	pw[0]=Node(1,1); For(i,1,MN-5) pw[i]=pw[i-1]*BASE;
	FI(s+1); n=strlen(s+1);
	foR(i,n,1) {
		if(s[i]==')') stk[++top]=i;
		else if(top) nxt[i]=stk[top--]+1;
//		cerr<<nxt[i]<<endl;
	}
	link(n+1,n+2,0);
	foR(i,n,1) {
		link(i,i+1,s[i]);
		if(nxt[i]&&fc(nxt[i],i)) link(i,f[nxt[i]][0],g[nxt[i]][0].x);	
	}
	
	int u=1;
	while(u!=n+2) {
		if(g[u][0].x) printf("%c",g[u][0].x);
		u=f[u][0];
//		cerr<<u<<endl;
	}
	printf("\n");
	return FastIO::Fflush(),0;
}
/*
  
*/