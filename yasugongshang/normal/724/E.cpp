#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sqr(x) ((x)*(x))
#define mp make_pair
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
inline void wri(ll a){write(a); putchar(' ');}
inline void writeln(ll a){write(a); puts("");}
const int N=10005;
ll ans,dq,q[N];
int n,a[N],C;
signed main(){
	n=read(); C=read();;
	for(int i=1;i<=n;i++){
		a[i]=read(); dq+=a[i];
	}
	for(int i=1;i<=n;i++){
		int b=read();
		q[i]=b-a[i]+(ll)(n-i+1)*C;
	}
	sort(&q[1],&q[n+1]);
	ans=dq;
	for(int i=1;i<=n;i++){
		dq+=q[i]; dq-=(ll)i*C;
		ans=min(ans,dq);
	}
	cout<<ans<<endl;
}
/*
 (n-p+1)-k
 
*/