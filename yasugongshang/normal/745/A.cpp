#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
#include <cstring>
#include <ctime>
#include <vector>
#define inf 1e9
#define ll long long
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Dow(i,j,k) for(int i=k;i>=j;i--)
using namespace std;
inline void read(int &tx){   ll x=0,f=1;char ch=getchar();   while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}  tx=x*f; }
inline void write(ll x){    if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10);   putchar(x%10+'0');  }
inline void writeln(ll x){write(x);puts("");}
using namespace std;
string s[1001],S; 
map<string,int>mp;
int ans;
int main() 
{
	cin>>S;
	int len=S.length();
	S=S+S;
	For(i,0,len)
		For(j,1,len)
			s[i]+=S[i+j-1];
	For(i,1,len) 	if(!mp[s[i]])	ans++,mp[s[i]]=1;
	printf("%d",ans);
}