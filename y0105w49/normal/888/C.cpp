// ayy
// ' lamo
// SUBLIME HAX
	#include <bits/stdc++.h>
	using namespace std;
	template<class T,class U>
	ostream &operator<<(ostream &os,const pair<T,U> &x) {
		return os<<"("<<x.first<<","<<x.second<<")";
	}
	namespace dbg_ns {
		template<typename C>
		struct is_iterable {
			template<class T> static long check(...);
			template<class T> static char check(int,
				typename T::const_iterator = C().end());
			enum {
				value = sizeof(check<C>(0)) == sizeof(char),
				neg_value = sizeof(check<C>(0)) != sizeof(char)
			};
		};
		template<class T> ostream &_out_str(ostream &os,const T &x) {
			return os<<'"'<<x<<'"';
		}
		template<class T> ostream &_dbg2_5(ostream &,const T &);
		template<bool B,typename T=void> using eit=typename enable_if<B,T>::type;
		template<class T>
		inline ostream &_dbg3(ostream &os,eit<is_iterable<T>::neg_value,const T> &x) {
			return os<<x;
		}
		template<class T>
		inline ostream &_dbg3(ostream &os,eit<is_iterable<T>::value,const T> &V) {
			os<<"{";
			bool ff=0;
			for(const auto &E:V) _dbg2_5(ff?os<<",":os,E), ff=1;
			return os<<"}";
		}
		template<>
		inline ostream &_dbg3<string>(ostream &os,const string &x) {
			return _out_str(os,x);
		}
		template<>
		inline ostream &_dbg3<const char *>(ostream &os,const char *const &x) {
			return _out_str(os,x);
		}
		template<class T> inline ostream &_dbg2_5(ostream &os,const T &x) {
			return _dbg3<T>(os,x);
		}
		template<class T,typename... Args> ostream &_dbg2(ostream &os,vector<string>::iterator nm,const T &x,Args&&... args);
		inline ostream &_dbg2(ostream &os,vector<string>::iterator) { return os; }
		template<typename... Args>
		inline ostream &_dbg2(ostream &os,vector<string>::iterator nm,const char *x,Args&&... args) {
			return _dbg2(_dbg3<const char *>(os<<"  ",x),nm+1,args...);
		}
		template<class T,typename... Args>
		inline ostream &_dbg2(ostream &os,vector<string>::iterator nm,const T &x,Args&&... args) {
			return _dbg2(_dbg3<T>(os<<"  "<<*nm<<"=",x),nm+1,args...);
		}
		vector<string> split(string s) {
			vector<string> Z;
			string z="";
			s+=',';
			int dep=0;
			for(char c:s) {
				if(c==',' && !dep) Z.push_back(z),z="";
				else z+=c;
				if(c=='(') ++dep;
				if(c==')') --dep;
			}
			return Z;
		}
		template<typename... Args> inline ostream &_dbg1(int ln,const string &nm,Args&&... args) {
			auto nms=split(nm);
			return _dbg2(cerr<<"L"<<ln<<":",nms.begin(),args...)<<endl;
		}
	}
	#define dbg(...) dbg_ns::_dbg1(__LINE__,#__VA_ARGS__,__VA_ARGS__)
	#define sz(x) (int(x.size()))
	#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	#define fi first
	#define se second
	#define pb push_back
// END SUBLIME HAX
// #include <bits/extc++.h>
// using namespace __gnu_pbds;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld; //CARE
typedef complex<ld> pt;
const ld eps=(ld)1e-8;
const ld tau=2*(ld)acosl(-1);
const int inf=1e9+99;
const ll linf=1e18+99;
const int P=1e9+7;





const int N=100<<10;
int n;
char s[N];
int ps[26][N];


bool kdom(int k) {
	for(int c=0;c<26;c++) {
		for(int i=0;i+k<=n;i++) if(!(ps[c][i+k]-ps[c][i])) goto die;
		return 1;
		die:;
	}
	return 0;
}


int32_t main() {
	scanf("%s",s+1);
	n=(int)strlen(s+1);
	// n=1e5;
	// for(int i=1;i<=n;i++) s[i]=char('a'+i*26/(n+1));

	for(int i=1;i<=n;i++) {
		ps[s[i]-'a'][i]=1;
	}
	for(int c=0;c<26;c++) partial_sum(ps[c],ps[c]+n+1,ps[c]);

	int L=1,R=n;
	for(;L!=R;) {
		int M=(L+R)>>1;
		if(kdom(M)) R=M;
		else L=M+1;
	}
	printf("%d\n",L);
}