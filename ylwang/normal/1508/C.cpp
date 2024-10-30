#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mkp make_pair
#define vi vector<int>
#define pii pair<int,int>
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
#define int long long
const int P=998244353; //
using namespace std;
template<typename T>inline void ckmax(T &a,T b) {(a<b)&&(a=b);}
template<typename T>inline void ckmin(T &a,T b) {(a>b)&&(a=b);}
inline int mul(int a,int b) {return 1ll*a*b%P;}
inline int add(int a,int b) {return a+b>=P?a+b-P:a+b;}
inline int sub(int a,int b) {return a-b>=0?a-b:a-b+P;}
inline void mulmod(int &a,int b) {a=mul(a, b);}
inline void addmod(int &a,int b) {((a+=b)>=P)&&(a-=P);}
inline void submod(int &a,int b) {((a-=b)<0)&&(a+=P);}
inline int ksm(int a,int b) {int ans=1; for(;b;b>>=1) {if(b&1) ans=1ll*ans*a%P;a=1ll*a*a%P;}return ans;}
inline void fprint(const vector<int> &f) {for(int i=0;i<(int)f.size();i++) fprintf(stderr,"%d ",f[i]); fprintf(stderr,"\n");}
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
}
inline int read() {int x; FI(x); return x;}
const int MN=2e5+5;
int n,m;
struct ele {
	int u,v,w;
	bool operator < (const ele &b) const {
		return w<b.w;
	}	
}g[MN];
vector<pii>e[MN];
set<int>lft;
struct dsu {
	static const int N=MN; int f[N];
	dsu()	{For(i,0,N-1) f[i]=i;}
	int find(int u) {
		return (u==f[u])?u:f[u]=find(f[u]);	
	}
	int merge(int u,int v) {
		if((u=find(u))==(v=find(v))) return 0;
		f[u]=v; return 1;
	}
}d,t;
int col[MN],tot;
ll ex;
void dfs(int u) {
	lft.erase(u); col[u]=tot;
	for(int v=0;;) {
		do {
			v++; v=*lft.lower_bound(v); if(v==n+1) return;
		} while((lower_bound(e[u].begin(),e[u].end(),mkp(v,0ll))->first)==v);
//		cerr<<u<<' '<<v<<endl;
		ex--; d.merge(u,v); dfs(v);
	}
}

signed main() {
	#ifndef ONLINE_JUDGE
		freopen("pro.in","r",stdin);
		freopen("pro.out","w",stdout);
	#endif
	n=read(),m=read(); ex=1ll*n*(n-1)/2-m;
	For(i,1,n) {
		lft.insert(i);	
	}
	lft.insert(n+1);
	int x=0;
	For(i,1,m) {
		int u=read(),v=read(),w=read(); x^=w;
		g[i]=(ele){u,v,w};
		e[u].pb(mkp(v,w)),e[v].pb(mkp(u,w));
	}
	For(u,1,n) {
		sort(e[u].begin(),e[u].end());
	}
	sort(g+1,g+1+m);
	For(u,1,n) {
		e[u].pb(mkp(n+2,0));
	}
	For(i,1,n) {
		if(!col[i]) {
			tot++; dfs(i);	
		}
//		cerr<<col[i]<<endl;
	}
//	cerr<<ex<<endl;
	assert(ex>=0);
//	if(ex>0&&m==199800) return 0; 
	ex=(ex==0);
	int ans=0;
	For(i,1,m) {
		int u=g[i].u,v=g[i].v,w=g[i].w;
//		cerr<<col[u]<<' '<<col[v]<<' '<<w<<endl;
		if(d.merge(u,v)) ans+=w,t.merge(u,v);
		else if(t.merge(u,v)) ckmin(x,w);
	}
//	cerr<<ans<<' '<<ex<<endl;
//	if(m==199800) cout<<ans<<endl;
	cout<<ans+ex*x<<endl;
	return FastIO::Fflush(),0;
}