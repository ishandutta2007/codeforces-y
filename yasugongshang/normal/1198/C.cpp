#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define mp make_pair
#define PI pair<int,int>
#define poly vector<int>
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
const int N=100005;
bool vis[N*3];
int main(){
	int T=read();
	while(T--){
		int n=read(),m=read();
		vector<int> ans;
		For(i,1,n*3)vis[i]=0;
		For(i,1,m){
			int x=read(),y=read();
			if(!vis[x]&&!vis[y]){
				vis[x]=vis[y]=1; ans.pb(i);
			}
		}
		if(ans.size()>=n){
			puts("Matching");
		}else{
			puts("IndSet");
			ans.clear();
			For(i,1,3*n)if(!vis[i])ans.pb(i);
		}
		For(i,0,n-1)wri(ans[i]); puts("");
	}
}