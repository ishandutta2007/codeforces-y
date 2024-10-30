#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define mp make_pair
#define PI pair<ll,ll>
#define poly vector<ll>
#define mem(a) memset((a),0,sizeof(a))
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
vector<int> v[N];
int dp[N][2],ans;
void dfs(int p,int fa){
	for(auto it=v[p].begin();it!=v[p].end();it++)if(*it==fa){
		v[p].erase(it); break;
	}
	dp[p][1]=1; dp[p][0]=v[p].size();
	vector<int> V[2];
	for(auto i:v[p]){
		dfs(i,p);
		dp[p][0]=max(dp[p][0],dp[i][1]+(int)v[p].size()-1);
		dp[p][1]=max(dp[p][1],dp[i][0]+1);
		V[0].pb(dp[i][0]);
		V[1].pb(dp[i][1]);
	}
	if(v[p].size()>=2)For(o,0,1){
		sort(V[o].begin(),V[o].end()); 
		reverse(V[o].begin(),V[o].end()); 
		if(o)ans=max(ans,V[o][0]+V[o][1]+(int)v[p].size()-2+(fa>0));
		else ans=max(ans,V[o][0]+V[o][1]+1);
	}
	dp[p][1]=max(dp[p][1],dp[p][0]);
	ans=max(ans,dp[p][1]);
	//cout<<p<<" "<<dp[p][0]<<" "<<dp[p][1]<<endl;
}
int main(){
	int n=read();
	For(i,1,n-1){
		int s=read(),t=read();
		v[s].pb(t); v[t].pb(s);
	}
	dfs(1,0);
	cout<<ans<<endl;
}