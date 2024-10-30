#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#define pii pair<int, int>
#define piii pair<int, pii>
#define pll pair<long long, long long>
#define plll pair<long long, pll>
#define tiii tuple<int, int, int>
#define tiiii tuple<int, int, int, int>
#define ff first
#define ss second
#define ee ss.ff
#define rr ss.ss
#define DEBUG
const int INF = (int)1e9 + 7;

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--)
    {
        int n; cin >> n;
        vector<int> A(n);
        for(int i = 0; i < n; ++i)
        {
            char c; cin >> c;
            A[i] = c - 'a';
        }
        auto B = A;
        sort(B.begin(), B.end());
        int cnt = 0;
        for(int i = 0; i < n; ++i) if(A[i] != B[i]) ++cnt;
        cout << cnt << '\n';
    }
}