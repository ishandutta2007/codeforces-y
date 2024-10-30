#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <utility>
namespace cm{class logger{private:std::ostream*_1a;std::string _13="\x2c\x20";bool _a=true;int _7=0;std::string _14="\033[0;31m";std::string _17="\033[0;32m";std::string _b="\033[0;33m";std::string _1b="\033[0;34m";std::string _11="\033[0;35m";std::string _15="\033[0;36m";std::string _16="\033[1;31m";std::string _18="\033[1;32m";std::string _8="\033[1;33m";std::string _19="\033[1;34m";std::string _1c="\033[1;35m";std::string _12="\033[1;36m";std::string _c="\033[0m";std::string _d(std::string _1d){if(_1d=="red")return _14;if(_1d=="green")return _17;if(_1d=="yellow")return _b;if(_1d=="blue")return _1b;if(_1d=="magenta")return _11;if(_1d=="cyan")return _15;if(_1d=="red bold")return _16;if(_1d=="green bold")return _18;if(_1d=="yellow bold")return _8;if(_1d=="blue bold")return _19;if(_1d=="magenta bold")return _1c;if(_1d=="cyan bold")return _12;if(_1d=="reset")return _c;return "";}public:logger(std::ostream&_1a):_1a(&_1a){}logger&set_ostream(std::ostream&_1a){this->_1a=&_1a;return*this;}logger&set_sep(const std::string&_13){this->_13=_13;return*this;}logger&assert_exit(){_a=true;return*this;}logger&assert_noexit(){_a=false;return*this;}logger&set_exit_code(int _2){_7=_2;return*this;}logger&endl(){*_1a<<std::endl;return*this;}logger&log(){return*this;}template<class Ta,class Tb,class...Tc>logger&log(const Ta&a,const Tb&b,Tc...c){return log(a).log(_13).log(b,c...);}template<class Ta,typename=decltype(std::cout<<std::declval<Ta>())>logger&log(const Ta&a){*_1a<<a;return*this;}template<class T,typename=decltype(std::declval<T>().begin()),typename=decltype(std::declval<T>().end()),typename=typename std::enable_if<!std::is_base_of<std::string,typename std::decay<T>::type>::value>::type,typename value_type=typename T::value_type>logger&log(const T&_e){log("{");for(auto it=_e.begin();it!=_e.end();++it){if(it!=_e.begin())log(_13);log(*it);}log("}");return*this;}template<class Ta,class Tb>logger&log(const std::pair<Ta,Tb>&x){return log("(").log(x.first,x.second).log(")");}
#if __cplusplus >= 201703L
template<class...T>logger&log(const std::tuple<T...>&x){log("(");std::apply([this](auto...x){this->log(x...);},x);return log(")");}
#else
template<class...T>logger&log(const std::tuple<T...>&){return log("<tuple>");}
#endif
template<class T>logger&hint(const T&x,std::string _f="cyan"){_f=_d(_f);return log(_f).log(x).log("\x3a\x20").log(_c);}template<class...T>logger&operator()(T..._10){return log(_10...).endl();}template<class...T>logger&_1(const std::string&_3,int _4,const std::string&_5,bool _10,const std::string&_9,T..._6){if(!_10){endl();hint(_3,"magenta").hint(_4,"magenta").log(_b).log("Assertion `").log(_8).log(_5).log(_b).log("` failed").log(_c).endl();if(_9!="")hint("detail","magenta").hint(_9)(_6...);if(_a)exit(_7);}return*this;}};namespace impl{logger see_logger(std::cout);}}
#define see(...)
#define asee(...)
#define cm_assert(...)
#include <cctype>
#include <cstdio>
namespace cm{template<class _1c,size_t _1b>class buffer_reader{protected:FILE*src;_1c*const buff;_1c*buff_end;_1c*buff_pos;void _11(){buff_end=buff+fread(buff,sizeof(_1c),_1b,src);buff_pos=buff;if(buff_end==buff){*buff_end='\0';}}public:buffer_reader(FILE*_14):src(_14),buff(new _1c[_1b]){_11();}buffer_reader(const buffer_reader&)=delete;buffer_reader(buffer_reader&&)=delete;buffer_reader&operator=(const buffer_reader&)=delete;buffer_reader&operator=(buffer_reader&&)=delete;_1c get()const{return*buff_pos;}_1c next(){_1c result=get();buff_pos++;if(buff_pos==buff_end)_11();return result;}~buffer_reader(){fclose(src);delete[]buff;}};using optimal_reader=buffer_reader<char,1<<16>;template<class _18>class scanner:protected _18{private:using _18::get;using _18::next;inline bool _15(char c){return c<=' ';}inline bool _17(char c){return c=='\n'||c=='\r';}int _16(){while(!isdigit(get())&&get()!='-')next();if(get()=='-')return next(),-1;return 1;}public:scanner()=delete;using _18::_18;char next_char(){while(_15(get()))next();return next();}char*next_token(char*s){while(_15(get()))next();while(!_15(get()))*s++=next();*s='\0';return s;}char*next_line(char*s){while(_15(get()))next();while(!_17(get()))*s++=next();*s='\0';return s;}int next_int(){int sign=_16();int result=0;while(isdigit(get()))result=result*10+(next()-'0');return sign*result;}long long next_long(){int sign=_16();long long result=0;while(isdigit(get()))result=result*10+(next()-'0');return sign*result;}template<class _19>_19 next_integer(){_19 sign=_16();_19 result(0);while(isdigit(get()))result=result*_19(10)+_19(next()-'0');return sign*result;}double next_double(){int sign=_16();double result=0;while(isdigit(get()))result=result*10+(next()-'0');if(get()=='.'){next();double cur_ep=0.1;while(isdigit(get()))result+=cur_ep*(next()-'0'),cur_ep*=0.1;}return sign*result;}};}
#include <utility>
#include <vector>
#define _1b inline __attribute__((always_inline))
namespace cm{template<class T>inline bool check_min(T&a,const T&b){return b<a?a=b,1:0;}template<class T>inline bool check_max(T&a,const T&b){return a<b?a=b,1:0;}struct once_t{bool _14=true;bool operator()(){return _14?(_14=false,true):false;}};}using cm::check_max;using cm::check_min;template<class A,class B>_1b std::pair<A,B>operator+(const std::pair<A,B>&lhs,const std::pair<A,B>&rhs){return std::make_pair(lhs.first+rhs.first,lhs.second+rhs.second);}template<class A,class B>_1b std::pair<A,B>operator-(const std::pair<A,B>&lhs,const std::pair<A,B>&rhs){return std::make_pair(lhs.first-rhs.first,lhs.second-rhs.second);}template<class A,class B>_1b std::pair<A,B>&operator+=(std::pair<A,B>&lhs,const std::pair<A,B>&rhs){lhs.first+=rhs.first;lhs.second+=rhs.second;return lhs;}template<class A,class B>_1b std::pair<A,B>&operator-=(std::pair<A,B>&lhs,const std::pair<A,B>&rhs){lhs.first-=rhs.first;lhs.second-=rhs.second;return lhs;}template<class T>std::vector<T>&operator+=(std::vector<T>&a,const std::vector<T>&b){a.insert(a.end(),b.begin(),b.end());return a;}template<class T>std::vector<T>&operator+=(std::vector<T>&a,const T&b){a.insert(a.end(),b);return a;}template<class T>std::vector<T>&operator+=(std::vector<T>&a,T&&b){a.insert(a.end(),std::forward<T>(b));return a;}template<class T>std::vector<T>operator+(std::vector<T>a,const std::vector<T>&b){a+=b;return a;}template<class T>std::vector<T>operator+(std::vector<T>a,T&b){a+=b;return a;}template<class T>std::vector<T>operator+(std::vector<T>a,T&&b){a+=std::forward<T>(b);return a;}
#define M__AT_INIT(line, Pred) struct CM_INNER_ATINIT##line##_17 {   CM_INNER_ATINIT##line## _17 () Pred } CM_INNER_ATINIT##line
#define M_AT_INIT(line, Pred) M__AT_INIT(line, Pred)
#define AT_INIT(Pred) M_AT_INIT(__LINE__, Pred)
#define M__AT_EXIT(line, Pred) struct CM_INNER_ATEXIT##line##_17 {   ~CM_INNER_ATEXIT##line## _17 () Pred } CM_INNER_ATEXIT##line
#define M_AT_EXIT(line, Pred) M__AT_EXIT(line, Pred)
#define AT_EXIT(Pred) M_AT_EXIT(__LINE__, Pred)
#define CONSTRAINT(n, a, b) constexpr auto n = a;
#undef _1b
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
cm::scanner<cm::optimal_reader>sc(stdin);constexpr long double eps=1e-9;constexpr long double eeps=1e-7;constexpr int N=100'005;constexpr int V=40'000'005;std::pair<int,int>p[N];long double k,ox,oy,a[N],b[N],cx[N],cy[N];long double ans,dis[N],s[N],t[N],tb[N];int n,m,q,rb[N],vol,stc[V];struct FTree{int f[N];void reset(int n){memset(f,0,(n+1)*4);}void modify(int u,int x){for(int i=u;i<=m;i+=i&-i){f[i]+=x;}}int query(int u){int res=0;for(int i=u;i>=1;i^=i&-i){res+=f[i];}return res;}int query(int l,int r){if(l>=r){return 0;}return query(r)-query(l);}}tr;long double get(int i,int j){long double x=(b[i]-b[j])/(a[j]-a[i]),y=a[i]*x+b[i];return std::sqrt((x-ox)*(x-ox)+(y-oy)*(y-oy));}bool check(long double k,bool typ){int res=0;m=0;for(int i=0;i<n;i++){long double x=cx[i]-ox,y=cy[i]-oy;if(dis[i]>k*k-eps){continue;}if(std::abs(dis[i])<eps){s[i]=std::atan2(a[i],1);t[i]=std::atan2(-a[i],-1);}else{long double z=std::sqrt(k*k/dis[i]-1);s[i]=std::atan2(y-x*z,x+y*z);t[i]=std::atan2(y+x*z,x-y*z);}if(s[i]>t[i]){std::swap(s[i],t[i]);}s[i]+=eps;t[i]-=eps;tb[m++]=s[i];tb[m++]=t[i];}std::sort(tb,tb+m);for(int i=0;i<n;i++){if(dis[i]>k*k-eps){p[i]={m,i};continue;}p[i]={std::upper_bound(tb,tb+m,s[i])-tb-1,i};rb[i]=static_cast<int>(std::upper_bound(tb,tb+m,t[i])-tb);}std::sort(p,p+n);if(!typ){tr.reset(m);for(int i=0;i<n;i++){if(p[i].first==m){break;}res+=tr.query(p[i].first,rb[p[i].second]);tr.modify(rb[p[i].second],1);if(res>=q){return false;}}}else{for(int i=0;i<n;i++){if(p[i].first==m)break;while(vol>0&&rb[stc[vol]]<=p[i].first)vol--;stc[++vol]=p[i].second;for(int i=vol-1;i>0;i--){if(rb[stc[i]]>rb[stc[i+1]])break;long double tmp=get(stc[i],stc[i+1]);ans+=tmp;res++;std::swap(stc[i],stc[i+1]);}}ans+=(q-res)*k;}return true;}int main(){n=sc.next_int();ox=sc.next_int()/1000.0;oy=sc.next_int()/1000.0;q=sc.next_int();int pass=0;for(int i=0;i<n;i++){a[i]=sc.next_int()/1000.0;b[i]=sc.next_int()/1000.0;if(std::abs(a[i])<eps){cx[i]=ox;cy[i]=b[i];}else{long double _12=-1/a[i],_d=oy-_12*ox;cx[i]=(_d-b[i])/(a[i]-_12);cy[i]=a[i]*cx[i]+b[i];}dis[i]=(ox-cx[i])*(ox-cx[i])+(oy-cy[i])*(oy-cy[i]);if(dis[i]<eps){pass++;}}if(pass*(pass-1ll)/2>=q){printf("0.000000\n");}else{for(long double l=eeps,r=21e8,mid;l<=r;){mid=(l+r)/2;if(check(mid,false)){l=mid+eeps;k=mid;}else{r=mid-eeps;}}check(k,true);printf("%.10f\n",static_cast<double>(ans));}return 0;}