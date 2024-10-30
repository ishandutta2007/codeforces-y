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

bool ask(vector<int>v){
	cout<<'?';
	for(auto x:v){
		cout<<' '<<x+1;
	}
	cout<<endl;
	string st;cin>>st;
	return st=="Red";
}

bool askl(int N,int l){
	vector<int>v(N);
	iota(v.begin(),v.end(),l);
	return ask(v);
}

// int check(int H,int W,int T,vector<vector<int>>field){

// }

const int mod = 1000000007;
struct Mod {
public:
	int num;
	Mod() : Mod(0) { ; }
	Mod(long long int n) : num((n % mod + mod) % mod) {
		static_assert(mod<INT_MAX / 2, "mod is too big, please make num 'long long int' from 'int'");
	}
	Mod(int n) : Mod(static_cast<long long int>(n)) { ; }
	operator int() { return num; }
};

Mod operator+(const Mod a, const Mod b) { return Mod((a.num + b.num) % mod); }
Mod operator+(const long long int a, const Mod b) { return Mod(a) + b; }
Mod operator+(const Mod a, const long long int  b) { return b + a; }
Mod operator++(Mod &a) { return a + Mod(1); }
Mod operator-(const Mod a, const Mod b) { return Mod((mod + a.num - b.num) % mod); }
Mod operator-(const long long int a, const Mod b) { return Mod(a) - b; }
Mod operator--(Mod &a) { return a - Mod(1); }
Mod operator*(const Mod a, const Mod b) { return Mod(((long long)a.num * b.num) % mod); }
Mod operator*(const long long int a, const Mod b) { return Mod(a)*b; }
Mod operator*(const Mod a, const long long int b) { return Mod(b)*a; }
Mod operator*(const Mod a, const int b) { return Mod(b)*a; }
Mod operator+=(Mod &a, const Mod b) { return a = a + b; }
Mod operator+=(long long int &a, const Mod b) { return a = a + b; }
Mod operator-=(Mod &a, const Mod b) { return a = a - b; }
Mod operator-=(long long int &a, const Mod b) { return a = a - b; }
Mod operator*=(Mod &a, const Mod b) { return a = a * b; }
Mod operator*=(long long int &a, const Mod b) { return a = a * b; }
Mod operator*=(Mod& a, const long long int &b) { return a = a * b; }
Mod operator^(const Mod a, const int n) {
	if (n == 0) return Mod(1);
	Mod res = (a * a) ^ (n / 2);
	if (n % 2) res = res * a;
	return res;
}
Mod mod_pow(const Mod a, const ll n) {
	if (n == 0) return Mod(1);
	Mod res = mod_pow((a * a), (n / 2));
	if (n % 2) res = res * a;
	return res;
}
Mod inv(const Mod a) { return a ^ (mod - 2); }
Mod operator/(const Mod a, const Mod b) {
	assert(b.num != 0);
	return a * inv(b);
}
Mod operator/(const long long int a, const Mod b) {
	return Mod(a) / b;
}
Mod operator/=(Mod &a, const Mod b) {
	return a = a / b;
}

#define MAX_MOD_N 1024000

Mod fact[MAX_MOD_N], factinv[MAX_MOD_N];
void init(const int amax = MAX_MOD_N) {
	fact[0] = Mod(1); factinv[0] = 1;
	for (int i = 0; i < amax - 1; ++i) {
		fact[i + 1] = fact[i] * Mod(i + 1);
		factinv[i + 1] = factinv[i] / Mod(i + 1);
	}
}
Mod comb(const int a, const int b) {
	return fact[a] * factinv[b] * factinv[a - b];
}
ll gcd(ll a,ll b){
	if(a%b==0)return b;
	else return gcd(b,a%b);
}

Mod solve(int H,int W,int T){
	T=1;
	Mod answer=0;
	// zero
	answer=1;

	// v only
	{
		ll kk=gcd(H,T);
		//WHATS(kk)
		Mod ff=mod_pow(2,kk);
		answer+=mod_pow(ff,W)-Mod(1);
	}
	// > only
	{
		ll kk=gcd(W,T);
		//WHATS(kk)
		Mod ff=mod_pow(2,kk);
		answer+=mod_pow(ff,H)-Mod(1);
	}
	//cout<<answer.num<<endl;

	// v>
	{
		ll hkk=gcd(H,T);
		ll wkk(gcd(W,T));
		//cout<<kk<<endl;
		ll sz=hkk*wkk;
		ll line_cnt=gcd(H/hkk,W/wkk);
		//WHATS(line_cnt)
		//WHATS(sz)
		//cout<<line_cnt<<endl;
		Mod num=mod_pow(2,line_cnt)+Mod(1);
		answer+=mod_pow(num,sz)-Mod(3);
	}
	//cout<<answer.num<<endl;
	return answer;
}
ll solve(ll amax){
	string st(to_string(amax));
	while(st.size()<19)st.insert(st.begin(),'0');

	vector<vector<vector<ll>>>cnts(20,vector<vector<ll>>(10,vector<ll>(2)));
	cnts[0][0][1]=1;
	for(int i=0;i<19;++i){
		int max_num=st[i]-'0';
		//WHATS(max_num)
		for(int nzero=0;nzero<5;++nzero){
			for(int same=1;same>=0;--same){
				for(int num=0;num<10;++num){
					int ncnt=nzero+(num!=0);
					if(same){
						if(num==max_num){
							cnts[i+1][ncnt][1]+=cnts[i][nzero][1];
						}else if(num<max_num){
							cnts[i+1][ncnt][0]+=cnts[i][nzero][1];
						}
					}else{
						cnts[i+1][ncnt][0]+=cnts[i][nzero][0];
					}
				}
			}
		}
	}
	//WHATS(cnts[19])
	ll answer=0;
	for(int nzero=0;nzero<=3;++nzero){
		for(int same=1;same>=0;--same){
			answer+=cnts[19][nzero][same];
		}
	}
	return answer;
}
vector<int>ge(){
	int N;cin>>N;
	vector<int>v(N);
	for(int i=0;i<N;++i)cin>>v[i];
	return v;
}
int main(){
	ios::sync_with_stdio(false);
	vector<int>av,bv;
	av=ge(),bv=ge();
	auto at=av.begin();
	auto bt=bv.begin();

	int answer=0;
	while(at!=av.end()||bt!=bv.end()){
		if(at==av.end()||bt==bv.end()){
			answer=-1;
			break;
		}else{
			ll aplus=0;
			aplus+=*at;
			at++;
			while(true){
				if(aplus>0){
					if(bt==bv.end()){
						answer=-1;
						break;
					}else{
						aplus-=*bt;
						bt++;
					}
				}else if(aplus<0){
					if(at==av.end()){
						answer=-1;
						break;

					}else{
						aplus+=*at;
						at++;
					}
				}else{
					break;
				}
			}
			if(answer!=-1){
				answer++;
			}else{
				break;
			}
		}
	}
		cout<<answer<<endl;

	return 0;
}