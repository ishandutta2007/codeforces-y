#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<bitset>
#include<ctime>
using namespace std;
typedef long long ll;
#define sqr(x) ((x)*(x))
#define mp make_pair
#define PI pair<int,int>
inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read(){
    int x = 0; char ch = gc(); bool positive = 1;
    for (; !isdigit(ch); ch = gc())	if (ch == '-')	positive = 0;
    for (; isdigit(ch); ch = gc())	x = x * 10 + ch - '0';
    return positive ? x : -x;
}
inline void write(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writeln(int a){
    if(a<0){
    	a=-a; putchar('-');
    }
    write(a); puts("");
}
const int N=100005;
int n,k;
char ch[N],ans[N];
int main(){
	n=read(); k=read();
	scanf("%s",ch+1);
	for(int i=1;i<=n;i++){
		if('z'-ch[i]>=ch[i]-'a'){
			if(k>='z'-ch[i]){
				k-='z'-ch[i]; ans[i]='z';
			}
			else{
				ans[i]=k+ch[i]; k=0;
			}
		}else{
			if(k>=ch[i]-'a'){
				k-=ch[i]-'a'; ans[i]='a';
			}else{
				ans[i]=ch[i]-k; k=0;
			}
		}
	}
	if(!k)puts(ans+1); else puts("-1");
}