#include <bits/stdc++.h>
using namespace std;

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define abs(a) max((a),-(a))
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define repe(i,n) rep(i,(n)+1)
#define per(i,n) for(int i=(int)(n)-1;i>=0;i--)
#define pere(i,n) rep(i,(n)+1)
#define all(x) (x).begin(),(x).end()
#define SP <<" "<<
#define RET return 0
#define MOD 1000000007
#define INF 1000000000000000000

typedef long long LL;
typedef long double LD;

int main(){
  LL n;
  cin >> n;
  if(n%2){
    for(LL i=3;i<=sqrt(n)+1;i++){
      if(n%i==0&&i!=n){
        cout << 1+(n-i)/2 << endl;
        return 0;
      }
    }
    cout << 1 << endl;
  }else{
    cout << n/2 << endl;
  }
  return 0;
}