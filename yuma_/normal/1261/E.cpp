#include "bits/stdc++.h"
#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<assert.h>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<stack>
#include<complex>
#pragma warning(disable:4996)
using namespace std;
using ld = long double;
template<class T>
using Table = vector<vector<T>>;
const ld eps=1e-9;
	
#define WHATS(var)cout<<__LINE__<<' '<<#var<<"="<<var<<endl;
	
template<class S, class T> ostream& operator <<(ostream &os, const pair<S, T> v){
os << "( " << v.first << ", " << v.second << ")"; return os;
}
template<class T> ostream& operator <<(ostream &os, const vector<T> &v){
for(int i = 0; i < v.size(); i++){if(i > 0){os << " ";} os << v[i];} return os;
}
template<class T> ostream& operator <<(ostream &os, const vector<vector<T>> &v){
for(int i = 0; i < v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}
template<class T> ostream& operator <<(ostream &os, const vector<set<T>> &v){
for(int i = 0; i < v.size(); i++){if(i > 0){os << endl;} os << v[i];} return os;
}
template<class T> ostream& operator <<(ostream &os, const set<T> &v){
int i=0;
for(auto it:v){
	if(i > 0){os << ' ';}
	os << it;
	i++;
} 
return os;
}
template<class T,class TT> ostream& operator <<(ostream &os, const map<T,TT> &v){
	int i=0;
	for(auto it:v){
		if(i > 0){os << ' ';}
		os << it;
		i++;
	} 
return os;
}
using ll = long long ;
	
namespace NTT{
using uint = uint_fast32_t;
	
// NTT_PRIMES {{{
constexpr ll NTT_PRIMES[][2] = {
	{1224736769, 3}, // 2^24 * 73 + 1,
	{1053818881, 7}, // 2^20 * 3 * 5 * 67 + 1
	{1051721729, 6}, // 2^20 * 17 * 59 + 1
	{1045430273, 3}, // 2^20 * 997 + 1
	{1012924417, 5}, // 2^21 * 3 * 7 * 23 + 1
	{1007681537, 3}, // 2^20 * 31^2 + 1
	{1004535809, 3}, // 2^21 * 479 + 1
	{998244353, 3},  // 2^23 * 7 * 17 + 1
	{985661441, 3},  // 2^22 * 5 * 47 + 1
	{976224257, 3},  // 2^20 * 7^2 * 19 + 1
	{975175681, 17}, // 2^21 * 3 * 5 * 31 + 1
	{962592769, 7},  // 2^21 * 3^3 * 17 + 1
	{950009857, 7},  // 2^21 * 4 * 151 + 1
	{943718401, 7},  // 2^22 * 3^2 * 5^2 + 1
	{935329793, 3},  // 2^22 * 223 + 1
	{924844033, 5},  // 2^21 * 3^2 * 7^2 + 1
	{469762049, 3},  // 2^26 * 7 + 1
	{167772161, 3},  // 2^25 * 5 + 1
};
// }}}
	
// general math {{{
ll extgcd(ll a, ll b, ll &x, ll &y) {
	ll d;
	return b == 0 ? (x = a < 0 ? -1 : 1, y = 0, a < 0 ? -a : a)
				: (d = extgcd(b, a % b, y, x), y -= a / b * x, d);
}
ll modinv(ll a, ll mod) {
	ll x, y;
	extgcd(a, mod, x, y);
	x %= mod;
	return x < 0 ? x + mod : x;
}
ll modpow(ll a, ll b, ll mod) {
	ll r = 1;
	a %= mod;
	while(b) {
	if(b & 1) r = r * a % mod;
	a = a * a % mod;
	b >>= 1;
	}
	return r;
}
// }}}
	
// NTT Core {{{
template < int MAX_H >
struct Pool {
	static ll *tmp, *A, *B;
};
template < int MAX_H >
ll *Pool< MAX_H >::tmp = new ll[1 << MAX_H];
template < int MAX_H >
ll *Pool< MAX_H >::A = new ll[1 << MAX_H];
template < int MAX_H >
ll *Pool< MAX_H >::B = new ll[1 << MAX_H];
	
template < int MAX_H, ll mod, ll primitive >
class Core {
public:
	static_assert((mod & ((1 << MAX_H) - 1)) == 1, "mod is too small; comment out");
	// ord zetaList[i] = 2^(i + 1)
	ll zetaList[MAX_H], zetaInvList[MAX_H];
	// constexpr
	Core() {
	zetaList[MAX_H - 1] = modpow(primitive, (mod - 1) / (1 << MAX_H), mod);
	zetaInvList[MAX_H - 1] = modinv(zetaList[MAX_H - 1], mod);
	for(int ih = MAX_H - 2; ih >= 0; --ih) {
		zetaList[ih] = zetaList[ih + 1] * zetaList[ih + 1] % mod;
		zetaInvList[ih] = zetaInvList[ih + 1] * zetaInvList[ih + 1] % mod;
	}
	}
	void fft(ll *a, uint n, uint nh, bool inverse) const {
	ll *tmp = Pool< MAX_H >::tmp;
	uint mask = n - 1;
	for(uint i = n >> 1, ih = nh - 1; i >= 1; i >>= 1, --ih) {
		ll zeta = inverse ? zetaInvList[nh - 1 - ih] : zetaList[nh - 1 - ih];
		ll powZeta = 1;
		for(uint j = 0; j < n; j += i) {
		for(uint k = 0; k < i; ++k) {
			tmp[j | k] =
				(a[((j << 1) & mask) | k] + powZeta * a[(((j << 1) | i) & mask) | k]) % mod;
		}
		powZeta = powZeta * zeta % mod;
		}
		swap(a, tmp);
	}
	if(nh & 1) {
		swap(a, tmp);
		for(uint i = 0; i < n; ++i) a[i] = tmp[i];
	}
	if(inverse) {
		ll invN = modinv(n, mod);
		for(uint i = 0; i < n; ++i) a[i] = a[i] * invN % mod;
	}
	}
	vector< ll > conv(const vector< ll > &a, const vector< ll > &b) const {
	uint t = a.size() + b.size() - 1;
	uint n = 1, nh = 0;
	while(n < t) n <<= 1, ++nh;
	return convStrict(a, b, n, nh);
	}
	vector< ll > convStrict(const vector< ll > &a, const vector< ll > &b, uint n,
							uint nh) const {
	ll *A = Pool< MAX_H >::A, *B = Pool< MAX_H >::B;
	for(uint i = 0; i < n; ++i) A[i] = B[i] = 0;
	copy(a.begin(), a.end(), A);
	copy(b.begin(), b.end(), B);
	fft(A, n, nh, 0), fft(B, n, nh, 0);
	for(uint i = 0; i < n; ++i) A[i] = A[i] * B[i] % mod;
	fft(A, n, nh, 1);
	return vector< ll >(A, A + n);
	}
};
// }}}
	
}
	
// 1st param is MAX_H
NTT::Core< 18, NTT::NTT_PRIMES[0][0], NTT::NTT_PRIMES[0][1] > nttBig;
NTT::Core< 18, 998244353, 5 > ntt;
	
	
vector<ll>solve(const vector<int>&v,int l,int r){
	//WHATS(l)
	//WHATS(r)
	if(l+1==r){
		return vector<ll>(v[l]+1,1);
	}
	int sum=accumulate(v.begin()+l,v.begin()+r,0);
	int x=l;
	int cnt=0;
	for(;x<r;++x){
		if(cnt+v[x]>sum/2){
			auto al=solve(v,l,x);
			auto ar=solve(v,x,r);
	
			auto av=ntt.conv(al,ar);
			av.resize(sum+1);
			//WHATS(av)
			return av;
		}
		cnt+=v[x];
	}
	return vector<ll>{1};
}
int main(){
	ios::sync_with_stdio(false);
	int N;cin>>N;
	vector<int>v(N);
	for(int i=0;i<N;++i)cin>>v[i];
	vector<pair<int,int>>ps{make_pair(0,N+1)};

	vector<vector<int>>field(N+1,vector<int>(N));
	for(int i=0;i<N;++i){
		int rest=v[i];
		vector<pair<int,int>>pluss;
		sort(ps.begin(),ps.end(),[](const pair<int,int>l,const pair<int,int>r){
			return l.second-l.first>r.second-r.first;
		});
		//WHATS(ps)
		bool flag=false;
		for(auto& p:ps){
			
			
			int use=min(rest,p.second-p.first-1);
			if(!flag){
				flag=true;
			}else{
				use=min(rest,p.second-p.first);

			}
			{
				for(int x=p.first;x<p.first+use;++x){
					field[x][i]=1;
				}
				if(p.first+use!=p.second)pluss.push_back(make_pair(p.first+use,p.second));

				p.second=p.first+use;
			}
			rest-=use;
			
			

		}
		for(auto pl:pluss){
			ps.emplace_back(pl);
		}
		vector<pair<int,int>>nps;
		for(auto p:ps){
			if(p.first!=p.second)nps.push_back(p);
		}
		ps=nps;
		//WHATS(ps)
	}
	cout<<N+1<<endl;
	for(int i=0;i<N+1;++i){
		for(int j=0;j<N;++j)cout<<field[i][j];
		cout<<endl;
	}
	return 0;
}