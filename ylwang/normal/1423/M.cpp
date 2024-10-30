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
inline int mul(int a,int b) {return 1ull*a*b%P;}
inline int add(int a,int b) {return a+b>=P?a+b-P:a+b;}
inline int sub(int a,int b) {return a-b>=0?a-b:a-b+P;}
inline void mulmod(int &a,int b) {a=mul(a, b);}
inline void addmod(int &a,int b) {((a+=b)>=P)&&(a-=P);}
inline void submod(int &a,int b) {((a-=b)<0)&&(a+=P);}
inline int ksm(int a,int b) {int ans=1; for(;b;b>>=1) {if(b&1) ans=1ll*ans*a%P;a=1ll*a*a%P;}return ans;}
inline void fprint(const int &x,char c=' ') {fprintf(stderr,"%lld%c",x,c);}
inline void fprint(const pii &x,char c='\n') {fprintf(stderr,"%lld %lld%c",x.first,x.second,c);}
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
inline int read() {int x; FI(x); return x;}
const int MN=2e5+5;
map<pii,int>mat;
int qry(int x,int y) {
	if(mat.count(mkp(x,y))) return mat[mkp(x,y)];
	cout<<"?"<<' '<<x<<' '<<y<<endl;
	int ans=0; cin>>ans; mat[mkp(x,y)]=ans; return ans;
}
vector<pii> solve(const vi &a,const vi &b) {
	if(a.size()==1) {
		pii mn=mkp(2e9,-1);
		for(int i=0;i<(int)b.size();i++) {
			int v=qry(a[0],b[i]);
			mn=min(mn,mkp(v,i));
		}
		return {mn};
	}
	if(a.size()>=b.size()) {
//		cerr<<"solve"<<endl;
//		fprint(a),fprint(b);
//		cerr<<endl;
		vi tmp;
		for(int i=0;i<(int)a.size();i+=2)
			tmp.pb(a[i]);
		vector<pii> res=solve(tmp,b),ans;
		for(int i=0;i<(int)a.size();i++) {
			if(i%2==0) ans.pb(res[i/2]);
			else {
				int l=res[i/2].second,r=(int)b.size()-1;	
				if(i!=(int)a.size()-1) r=res[i/2+1].second;
				pii mn=mkp(2e9,-1);
				For(j,l,r) {
					int v=qry(a[i],b[j]);
					mn=min(mn,mkp(v,j));
				}
				ans.pb(mn);
			}
		}
		return ans;
	} else {
//		cerr<<"reduce"<<endl;
//		fprint(a),fprint(b);
//		cerr<<endl;
		vi s(1,b[0]); int top=0;
		for(int i=1;i<(int)b.size();i++) {
			int fl=1;
			while(s.size()) {
				int vl=qry(a[top],s[top]);
				int vr=qry(a[top],b[i]);
				if(vl<=vr) {
					if(s.size()==a.size()) fl=0;
					break;	
				}
				s.pop_back(); top--;
			}
			if(fl) ++top,s.push_back(b[i]);
//			cerr<<"*"<<' '<<i<<' '<<s.size()<<endl;
		}
		vector<pii>ans=solve(a,s);
		int pos=0;
		for(int i=0;i<(int)ans.size();i++) {
			while(s[ans[i].second]>b[pos]) pos++;
			ans[i].second=pos;
		}
		return ans;
	}
}
int n,m;
signed main() {
	cin>>n>>m; 
	vi a(n),b(m);
	For(i,0,n-1) a[i]=i+1;
	For(i,0,m-1) b[i]=i+1;
	vector<pii> res=solve(a,b);
	int ans=INF;
	For(i,0,n-1) {
		ckmin(ans,res[i].first);
	}
	cout<<"!"<<' '<<ans<<endl;
	return FastIO::Fflush(),0;
}