#include<bits/stdc++.h>
using namespace std;

const int N=1e5+1e3+7;

int T;

int n,a[N],ans[N];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int L=1,R=n/2+1;
	for(int i=1;i<=n;i+=2)
		ans[i]=a[R++];
	for(int i=2;i<=n;i+=2)
		ans[i]=a[L++];
	for(int i=2;i<n;i++)
		ans[0]+=(ans[i]<ans[i-1]&&ans[i]<ans[i+1]);
	printf("%d\n",ans[0]);
	for(int i=1;i<=n;i++)
		printf("%d%c",ans[i]," \n"[i==n]);
}