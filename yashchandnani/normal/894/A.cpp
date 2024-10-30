#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long double ld; 

typedef set<int>::iterator sit;
typedef map<int,int>::iterator mit;
typedef vector<int>::iterator vit;

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 3;

#define _  %  MOD
#define __ %= MOD

#define      each(it,s)        for(sit it = s.begin(); it != s.end(); ++it)
#define      sortA(v)          sort(v.begin(), v.end())
#define      sortD(v)          sort(v.rbegin(), v.rend())
#define      fill(a)           memset(a, 0, sizeof (a))

#define      rep(i, n)         for(int i = 0; i < (n); ++i)
#define      repA(i, a, n)     for(int i = a; i <= (n); ++i)
#define      repD(i, a, n)     for(int i = a; i >= (n); --i)
#define 	 pq(x)			   priority_queue<x,std::vector<x>,compare>
#define 	 rpq(x)			   priority_queue<x,std::vector<x>,Rcompare>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SZ(x) ((int) (x).size())
#define fbo find_by_order
#define ook order_of_key
struct Rcompare
{
  bool operator()(ii lhs,ii rhs){
    return lhs.fi>rhs.fi;
  }
};
struct compare
{
  bool operator()(ii lhs,ii rhs){
    return lhs.fi<rhs.fi;
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;cin>>s;
  int n = s.size();
  int ans[n+1][3];
  ans[0][0]=ans[0][1]=ans[0][2]=0;
  rep(i,n){
  	if(s[i]=='Q'){
  		ans[i+1][0] = ans[i][0]+1;
  		ans[i+1][1] = ans[i][1];
  		ans[i+1][2] = ans[i][2]+ans[i][1];
  	}
  	else if(s[i]=='A'){
  		ans[i+1][0] = ans[i][0];
  		ans[i+1][1] = ans[i][1]+ans[i][0];
  		ans[i+1][2] = ans[i][2];
  	}
  	else{
  		ans[i+1][0] = ans[i][0];
  		ans[i+1][1] = ans[i][1];
  		ans[i+1][2] = ans[i][2];
  	}

  }
  cout<<ans[n][2]<<endl;
  return 0;
}