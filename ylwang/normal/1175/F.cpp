#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define ll long long
#define pb emplace_back
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
#define int ll
const int P=998244353; //
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
int n,a[MN],lst[MN],lft[MN],s[MN],top,smx[MN],pmx[MN];
vi pos[MN];
struct ST {
	static const int N=MN;
	int mn[20][N],mx[20][N],lg[N],n;
	void init(int n,int *vmn,int *vmx) {
//		fprint(vmn,n),fprint(vmx,n);
		lg[1]=0; For(i,2,n) lg[i]=lg[i>>1]+1;
		For(i,1,n) mn[0][i]=vmn[i],mx[0][i]=vmx[i];
		For(i,1,19) {
			For(j,1,n-(1<<i)+1) {
				mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<(i-1))]);
				mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
			}
		}
	}
	int qmn(int l,int r) {
		int d=lg[r-l+1]; return min(mn[d][l],mn[d][r-(1<<d)+1]);
	}
	int qmx(int l,int r) {
		int d=lg[r-l+1]; return max(mx[d][l],mx[d][r-(1<<d)+1]);
	}
	
} st;
int find_pre(int x) { // the last 
	int l=1,r=x-1,ans=x;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(st.qmx(mid,x-1)<a[x]) r=mid-1,ans=mid;
		else l=mid+1;
	}
	return ans;
}
int find_nxt(int x) {
	int l=x+1,r=n,ans=x;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(st.qmx(x+1,mid)<a[x]) l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans;	
}
void works() {
	n=read(); For(i,1,n) a[i]=read(),smx[i]=pmx[i]=a[i];	int mx=0,ans=0;
	st.init(n,a,a);
	For(i,1,n) pos[a[i]].pb(i);
	For(i,1,n) {
		ckmax(mx,lst[a[i]]+1); lft[i]=mx;
		lst[a[i]]=i;
	}
//	fprint(lft,n);
	foR(x,n,1) {
		for(auto i:pos[x]) {
			int pre=find_pre(i),nxt=find_nxt(i);
//			cerr<<i<<' '<<pre<<' '<<nxt<<endl;
			For(j,pre,nxt-x+1) ans+=j>=lft[j+x-1];
		}
	}
	cout<<ans<<endl;
}
signed main() {
	#ifndef ONLINE_JUDGE
		freopen("pro.in","r",stdin);
		freopen("pro.out","w",stdout);
	#endif
	int T=1;
	while(T--) {
		works();
	}
	return FastIO::Fflush(),0;
}
/*
?t??? 1??? 12?
*/