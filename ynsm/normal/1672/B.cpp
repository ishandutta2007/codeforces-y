#include <bits/stdc++.h>

#define f first
#define s second
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;

const int N = (int)2e5 + 123, inf = 1e9, mod = 1e9 + 7;
const ll INF = 1e18;

char s[N];
int n;

void solve()
{
    scanf("%s", s);
    n = strlen(s);
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'A')
            cnt++;
        else
            cnt--;
        if (cnt < 0)
        {
            printf("NO\n");
            return;
        }
    }
    if (s[n - 1] == 'B')
        printf("YES\n");
    else
        printf("NO\n");
}
int main()
{
    int t = 1;
    scanf("%d", &t);
    while (t--)
        solve();
}