#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
inline void write(int a){
	if(a>=10)write(a/10);
	putchar('0'+a%10);
}
inline void writeln(int a){
	write(a); puts("");
}
inline int	read()// 
{
	int x = 0; char ch = getchar(); bool positive = 1;
	for (; !isdigit(ch); ch = getchar())	if (ch == '-')	positive = 0;
	for (; isdigit(ch); ch = getchar())	x = x * 10 + ch - '0';
	return positive ? x : -x;
}
int main(){
	int n=read();
	for(int i=0;i+4<=n;i+=4){
		putchar('a'); putchar('a'); putchar('b'); putchar('b');
	}
	n=n%4;
	if(n){
		putchar('a'); n--;
	}
	if(n){
		putchar('a'); n--;
	}
	if(n)putchar('b');
}