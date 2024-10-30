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
inline void fprint(const pii &x,char c='\n') {fprintf(stderr,"%d %d%c",x.first,x.second,c);}
inline void fprint(const int &x,char c=' ') {fprintf(stderr,"%d%c",x,c);}
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
const int MN=1e5+5;
int n,m;
struct BIT {
	int c[MN];
	void upd(int x,int v) {
		for(;x<=n;x+=x&-x) c[x]+=v;
	}
	int qry(int x) {
		int ans=0; for(;x;x-=x&-x) ans+=c[x];
		return ans;
	}
	
	int getkth(int k) {
//		cerr<<"getkth "<<k<<endl;
		int ans=0,sum=0;
		for(int i=18;i>=0;i--) {
//			cerr<<i<<endl;
			if(ans+(1<<i)>n) continue;
			if(sum+c[ans+(1<<i)]<k) {
				ans+=(1<<i),sum+=c[ans];	
			}
		}
//		cerr<<ans+1<<endl;
		return ans+1;
	}
} tr;
struct ele {
	int x,k,id; // x : x, y : k, z : id
	ele(){} ele(int X,int K,int Z):x(X),k(K),id(Z){}
};
ele q[MN];
bool cmp1(const ele &x,const ele &y) {return x.x<y.x;	}
bool cmp2(const ele &x,const ele &y) {return x.k<y.k;	}
int a[MN];

int ans[MN];
signed main() {
	#ifndef ONLINE_JUDGE
		freopen("pro.in","r",stdin);
		freopen("pro.out","w",stdout);
	#endif
	n=read(),m=read();
	For(i,1,n) a[i]=read(); int now=0; int tttm=m;
	For(i,1,m) {
		q[i].x=read(),q[i].k=read(),q[i].id=++now;	
		if(q[i].x<a[1]) {
			ans[now]=q[i].x;
			i--,m--;
		}
	}
	sort(q+1,q+1+m,cmp1); now=m;
	For(i,1,n) tr.upd(i,1);
	int cur=1.1e15,tim=0;
	foR(i,n,1) {
		int go=(cur-a[i]+i-1)/i,to=cur-go*i;
		while(now&&q[now].x>=to) {
			int gonow=(cur-q[now].x+i-1)/i,tonow=cur-gonow*i;
			q[now].k=tim+gonow-q[now].k,q[now].x=tr.getkth(q[now].x-tonow+1);
			now--;
		}
		cur=to; tim+=go;
		while(i&&a[i]>=cur) {
			int pos=tr.getkth(a[i]-cur+1);
			tr.upd(pos,-1); i--;
		} i++;
	}
	sort(q+1,q+1+m,cmp2); 
	cur=1.1e15,tim=0,now=0;
	For(i,1,n) tr.upd(i,1);
	foR(i,n,1) {
		int go=(cur-a[i]+i-1)/i,to=cur-go*i;
		while(now<=m&&q[now].k<=tim+go) {
			ans[q[now].id]=cur+tr.qry(q[now].x)-(q[now].k-tim)*i-1;
			now++;
		}
		cur=to; tim+=go;
		while(i&&a[i]>=cur) {
			int pos=tr.getkth(a[i]-cur+1);
			tr.upd(pos,-1); i--;
		} i++;
	}
	For(i,1,tttm) {
		FO(ans[i]); FO('\n');
	}
	return FastIO::Fflush(),0;
}

/*
// p[i] < p[j] : iff pos[i] > j && a[i] < j
*/