#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(int i = (k); i <= (j); i++)
#define INF 2147483647
#define eps 1e-4
using namespace std;
inline int read()
{
    int num = 0; char c=' '; int flag = 1;
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num * flag;
}

signed main()
{
	int n = read(), m = read();
	if(m == 0) {
		cout << n << ' ' << n << endl;
	} else if(n == 0) {
		cout << "Impossible" << endl;
	} else {
		cout << max(n, m) << ' ' << n + m - 1 << endl;
	}
    return 0;
}
/*

*/