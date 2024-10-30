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
const int N=300005;
int a[N],n,m;
bool check(int x){
	int t=0;
	For(i,1,n){
		if(a[i]+x>=m){
			if(a[i]+x-m<t)t=max(t,a[i]);
		}else{
			if(a[i]+x<t)return 0;
			else t=max(t,a[i]);
		}
	}
	return 1;
}
int main(){
	n=read(),m=read();
	For(i,1,n)a[i]=read();
	int l=0,r=m-1;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid; else l=mid+1;
	}
	cout<<l<<endl;
}
/*
dp[i][j]=min(dp[i-1][k],j-k)
*/