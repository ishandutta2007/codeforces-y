#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sqr(x) ((x)*(x))
#define mp make_pair
#define ld long double
#define PI pair<int,int>
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
const int N=1005;
int n,m,v[N],zs[N],p[N],q[N],tong[N],ans[N][N],vis[N];
char ch[N][N];
int main(){
	n=read(); int SAJB=0;
	for(int i=1;i<=n;i++){p[read()]=i; }
	for(int i=1;i<=n;i++)SAJB+=abs(p[i]-i);
	if(SAJB==0){
		writeln(n);
		for(int i=1;i<=n;i++){for(int j=1;j<=n;j++)putchar('.'); puts("");}return 0;
	}
	writeln(n-1);
	for(int i=1;i<=n;i++)if(p[i]!=i){
		q[++m]=p[i]; tong[i]=m;
	}
	for(int i=1;i<=m;i++)q[i]=tong[q[i]];
	memset(ans,-1,sizeof(ans)); int dd;
	for(int i=1;i<=m;i++)if(!vis[i]){
		int jj=1;
		for(int j=q[i];j!=i;j=q[j])jj++;
		if(i==1){
			int dq=jj-1; dd=jj;
			for(int j=i;q[j]!=i;j=q[j]){
				vis[q[j]]=1; ans[dq][j]=j<q[j]; ans[dq][q[j]]=ans[dq][j]; dq--;  //cout<<dq<<" "<<j<<" "<<q[j]<<endl;
			} vis[1]=1;
			continue;
		}
		int l=dd,r=dd+jj-1,dq=r;
		for(int j=i;;j=q[j]){
			vis[j]=1; 
			if(q[j]==i){
				ans[l][j]=ans[l][1]=0; ans[r][1]=1; break;
			}
			ans[dq][j]=j<q[j]; ans[dq][q[j]]=ans[dq][j]; dq--;
		}
		dd+=jj;
	}
	//for(int i=1;i<=m;i++)cout<<q[i]<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int t=ans[tong[i]][tong[j]]; if(t==-1)putchar('.'); else if(t)putchar('\\'); else putchar('/');
		}puts("");
	}
}