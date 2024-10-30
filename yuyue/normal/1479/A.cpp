#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for (int i=(a);i<=(b);++i)
#define DF(i,a,b) for (int i=(a);i>=(b);--i)
using namespace std;
inline int read(){
	char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int M=1e5+10;
int n,a[M],vis[M];
int qry(int x){
	if (x<=0 || x>n) return 1e9; 
	if (!vis[x]){
		cout<<"? "<<x<<endl;
		cin>>a[x];
		vis[x]=1;
		return a[x];
	}
	return a[x];
}
int main(){
	cin>>n;
	int l=1,r=n;
	while (l<=r){
		int mid=(l+r>>1);
		int x=qry(mid-1),y=qry(mid),z=qry(mid+1);
		int mi=min(x,min(y,z));
		if (mi==y){
			cout<<"! "<<mid<<endl;
			return 0;
		}
		else{
			if (mi==x) r=mid-1;
			else l=mid+1;
		}
	}
	return 0;
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/