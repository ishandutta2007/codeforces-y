#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define mp make_pair
#define PI pair<int,int>
#define For(i,l,r) for(int i=(int)(l);i<=(int)(r);i++)
#define Rep(i,r,l) for(int i=(int)(r);i>=(int)(l);i--)
#define pb push_back
#define fi first
#define se second
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
inline ull rnd(){
	return ((ull)rand()<<30^rand())<<4|rand()%4;
}
const int N=200005;
int a[N],b[N];
int main(){
	int n=read(),m=read(),ta=read(),tb=read(),k=read();
	For(i,1,n)a[i]=read();
	For(i,1,m)b[i]=read();
	int t=1,ans=0;
	if(k>=n||k>=m){puts("-1"); return 0;}
	For(i,1,k+1){
		while(b[t]<a[i]+ta&t<=m)t++;
		//cout<<i<<" "<<t<<" "<<endl;
		if(m-t+i<=k){puts("-1"); return 0;}
		ans=max(ans,b[t+k-(i-1)]+tb);
	}
	cout<<ans<<endl;
}