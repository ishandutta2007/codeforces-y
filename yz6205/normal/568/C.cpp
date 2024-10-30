#ifndef CM_DEBUG_H
#define CM_DEBUG_H 1
#include <iostream>
#include <utility>
#include <tuple>
#include <iterator>
#include <string>
namespace cm{class logger{private:std::ostream*out;std::string sep="\x2c\x20";bool _assert_exit=true;std::string c_red="\033[0;31m";std::string c_green="\033[0;32m";std::string c_yellow="\033[0;33m";std::string c_blue="\033[0;34m";std::string c_magenta="\033[0;35m";std::string c_cyan="\033[0;36m";std::string c_red_bold="\033[1;31m";std::string c_green_bold="\033[1;32m";std::string c_yellow_bold="\033[1;33m";std::string c_blue_bold="\033[1;34m";std::string c_magenta_bold="\033[1;35m";std::string c_cyan_bold="\033[1;36m";std::string c_reset="\033[0m";std::string get_color(std::string name){if(name=="red")return c_red;if(name=="green")return c_green;if(name=="yellow")return c_yellow;if(name=="blue")return c_blue;if(name=="magenta")return c_magenta;if(name=="cyan")return c_cyan;if(name=="red bold")return c_red_bold;if(name=="green bold")return c_green_bold;if(name=="yellow bold")return c_yellow_bold;if(name=="blue bold")return c_blue_bold;if(name=="magenta bold")return c_magenta_bold;if(name=="cyan bold")return c_cyan_bold;if(name=="reset")return c_reset;return "";}public:logger(std::ostream&out):out(&out){}logger&set_ostream(std::ostream&out){this->out=&out;return*this;}logger&set_sep(const std::string&sep){this->sep=sep;return*this;}logger&assert_exit(){_assert_exit=true;return*this;}logger&assert_noexit(){_assert_exit=false;return*this;}logger&endl(){*out<<std::endl;return*this;}logger&log(){return*this;}template<class Ta,class Tb,class...Tc>logger&log(const Ta&a,const Tb&b,Tc...c){return log(a).log(sep).log(b,c...);}template<class Ta,typename=decltype(std::cout<<std::declval<Ta>())>logger&log(const Ta&a){*out<<a;return*this;}template<class T,typename=decltype(std::declval<T>().begin()),typename=decltype(std::declval<T>().end()),typename=typename std::enable_if<!std::is_base_of<std::string,typename std::decay<T>::type>::value>::type,typename value_type=typename T::value_type>logger&log(const T&container){log("{");for(auto it=container.begin();it!=container.end();++it){if(it!=container.begin())log(sep);log(*it);}log("}");return*this;}template<class Ta,class Tb>logger&log(const std::pair<Ta,Tb>&x){return log("(").log(x.first,x.second).log(")");}
#if __cplusplus >= 201703L
template<class...T>logger&log(const std::tuple<T...>&x){log("(");std::apply([this](auto...x){this->log(x...);},x);return log(")");}
#else
template<class...T>logger&log(const std::tuple<T...>&){return log("<tuple>");}
#endif
template<class T>logger&hint(const T&x,std::string color="cyan"){color=get_color(color);return log(color).log(x).log("\x3a\x20").log(c_reset);}template<class...T>logger&operator()(T...value){return log(value...).endl();}template<class...T>logger&_assert(const std::string&file,int line,const std::string&raw,bool value,const std::string&info_str,T...info){if(!value){endl();hint(file,"magenta").hint(line,"magenta").log(c_yellow).log("Assertion `").log(c_yellow_bold).log(raw).log(c_yellow).log("` failed").log(c_reset).endl();if(info_str!="")hint("detail","magenta").hint(info_str)(info...);if(_assert_exit)exit(0);}return*this;}};namespace impl{logger see_logger(std::cout);}}
#ifdef CM_DEBUG
#define see(arg...) cm::impl::see_logger.hint(#arg)(arg)
#define asee(arg...) cm::impl::see_logger.hint(__FILE__, "magenta").hint(__LINE__, "magenta").hint(#arg)(arg)
#define cm_assert(val, arg...) cm::impl::see_logger._assert(__FILE__, __LINE__, #val, val, #arg, ##arg)
#else
#define see(...)
#define asee(...)
#define cm_assert(...)
#endif
#endif
#ifndef CM_SCANNER_H
#define CM_SCANNER_H
#include <cstdio>
#include <cctype>
namespace cm{template<class Type,size_t buf_size>class buffer_reader{protected:FILE*src;Type*const buff;Type*buff_end;Type*buff_pos;void flush(){buff_end=buff+fread(buff,sizeof(Type),buf_size,src);buff_pos=buff;if(buff_end==buff){*buff_end='\0';}}public:buffer_reader(FILE*src):src(src),buff(new Type[buf_size]){flush();}buffer_reader(const buffer_reader&)=delete;buffer_reader(buffer_reader&&)=delete;buffer_reader&operator=(const buffer_reader&)=delete;buffer_reader&operator=(buffer_reader&&)=delete;Type get()const{return*buff_pos;}Type next(){Type result=get();buff_pos++;if(buff_pos==buff_end)flush();return result;}~buffer_reader(){fclose(src);delete[]buff;}};
#ifdef CM_DEBUG
using optimal_reader=buffer_reader<char,1>;
#else
using optimal_reader=buffer_reader<char,1<<16>;
#endif
template<class BufferReader>class scanner:protected BufferReader{private:using BufferReader::get;using BufferReader::next;inline bool is_ws(char c){return c<=' ';}inline bool is_cr(char c){return c=='\n'||c=='\r';}int get_sign(){while(!isdigit(get())&&get()!='-')next();if(get()=='-')return next(),-1;return 1;}public:scanner()=delete;using BufferReader::BufferReader;char next_char(){while(is_ws(get()))next();return next();}char*next_token(char*s){while(is_ws(get()))next();while(!is_ws(get()))*s++=next();*s='\0';return s;}char*next_line(char*s){while(is_ws(get()))next();while(!is_cr(get()))*s++=next();*s='\0';return s;}int next_int(){int sign=get_sign();int result=0;while(isdigit(get()))result=result*10+(next()-'0');return sign*result;}long long next_long(){int sign=get_sign();long long result=0;while(isdigit(get()))result=result*10+(next()-'0');return sign*result;}long long next_modint(long long mod){get_sign();long long result=0;while(isdigit(get()))result=(result*10+(next()-'0'))%mod;return result;}double next_double(){int sign=get_sign();double result=0;while(isdigit(get()))result=result*10+(next()-'0');if(get()=='.'){next();double cur_ep=0.1;while(isdigit(get()))result+=cur_ep*(next()-'0'),cur_ep*=0.1;}return sign*result;}};}
#endif
#ifndef CM_UTIL_H
#define CM_UTIL_H 1
#include <utility>
#include <vector>
namespace cm{template<class T>inline bool check_min(T&a,const T&b){return b<a?a=b,1:0;}template<class T>inline bool check_max(T&a,const T&b){return a<b?a=b,1:0;}struct once_t{bool once=true;bool operator()(){return once?(once=false,true):false;}};}using cm::check_min;using cm::check_max;template<class A,class B>inline __attribute__((always_inline))std::pair<A,B>operator+(const std::pair<A,B>&lhs,const std::pair<A,B>&rhs){return std::make_pair(lhs.first+rhs.first,lhs.second+rhs.second);}template<class A,class B>inline __attribute__((always_inline))std::pair<A,B>operator-(const std::pair<A,B>&lhs,const std::pair<A,B>&rhs){return std::make_pair(lhs.first-rhs.first,lhs.second-rhs.second);}template<class A,class B>inline __attribute__((always_inline))std::pair<A,B>&operator+=(std::pair<A,B>&lhs,const std::pair<A,B>&rhs){lhs.first+=rhs.first;lhs.second+=rhs.second;return lhs;}template<class A,class B>inline __attribute__((always_inline))std::pair<A,B>&operator-=(std::pair<A,B>&lhs,const std::pair<A,B>&rhs){lhs.first-=rhs.first;lhs.second-=rhs.second;return lhs;}template<class T>std::vector<T>&operator+=(std::vector<T>&a,const std::vector<T>&b){a.insert(a.end(),b.begin(),b.end());return a;}template<class T>std::vector<T>&operator+=(std::vector<T>&a,const T&b){a.insert(a.end(),b);return a;}template<class T>std::vector<T>&operator+=(std::vector<T>&a,T&&b){a.insert(a.end(),std::forward<T>(b));return a;}template<class T>std::vector<T>operator+(std::vector<T>a,const std::vector<T>&b){a+=b;return a;}template<class T>std::vector<T>operator+(std::vector<T>a,T&b){a+=b;return a;}template<class T>std::vector<T>operator+(std::vector<T>a,T&&b){a+=std::forward<T>(b);return a;}
#define __AT_INIT(line, Pred) struct CM_INNER_ATINIT##line##_t { \
CM_INNER_ATINIT##line## _t()Pred}CM_INNER_ATINIT##line
#define _AT_INIT(line, Pred) __AT_INIT(line, Pred)
#define AT_INIT(Pred) _AT_INIT(__LINE__, Pred)
#define __AT_EXIT(line, Pred) struct CM_INNER_ATEXIT##line##_t { \
~CM_INNER_ATEXIT##line## _t()Pred}CM_INNER_ATEXIT##line
#define _AT_EXIT(line, Pred) __AT_EXIT(line, Pred)
#define AT_EXIT(Pred) _AT_EXIT(__LINE__, Pred)
#endif
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <string>
#define int long long

int n, e[405][405];
void floyd()
{
  for (int k = 1; k <= n + n; k++)
    for (int i = 1; i <= n + n; i++)
      for (int j = 1; j <= n + n; j++)
        e[i][j] |= (e[i][k] && e[k][j]);
}

int acv[405], tcv[405];
int mxp[2], vc[35], nxt[35], nxu[35];
std::string s;

int check(int pos, int now, int x, int id)
{
  int tmp;
  if (acv[pos] != -1 && acv[pos] != vc[now])
    return 0;
  for (int i = 1; i <= n; i++)
    if (e[x][i] && e[x][i + n])
      return 0;

  for (int i = 1; i <= n; i++)
  {
    tcv[i] = -1;
    if (e[x][i])
      tcv[i] = 0;
    if (e[x][i + n])
      tcv[i] = 1;
  }
  if (!id)
  {
    for (int i = 1; i <= n; i++)
    {
      if (pos + i > n)
        break;
      tmp = std::max(tcv[pos + i], acv[pos + i]);
      if (tmp == -1)
        break;
      if (mxp[tmp] < s[pos + i] - 'a' + 1)
        return 0;
      if (mxp[tmp] > s[pos + i] - 'a' + 1)
        break;
    }
  }
  for (int i = 1; i <= n; i++)
    acv[i] = std::max(acv[i], tcv[i]);
  return 1;
}

int ans[405];
signed main()
{
  int len, m, l1, l2, c1, c2, fla;
  char ch1, ch2;
  std::cin >> s;
  len = s.length();
  s = ' ' + s;
  for (int i = 1; i <= len; i++)
    vc[i] = (s[i] == 'C' ? 0 : 1);
  vc[len + 1] = -1; 
  mxp[0] = mxp[1] = -1;
  for (int i = 1; i <= len; i++)
    mxp[vc[i]] = i;

  for (int i = 1; i <= len; i++)
  {
    nxt[i] = 0;
    for (int j = i + 1; j <= len; j++)
      if (vc[i] != vc[j])
      {
        nxt[i] = j;
        break;
      }
  }
  for (int i = 1; i <= len; i++)
  {
    nxu[i] = 0;
    for (int j = i + 1; j <= len; j++)
      if (vc[i] == vc[j])
      {
        nxu[i] = j;
        break;
      }
  }

  memset(acv, -1, sizeof(acv));
  memset(tcv, -1, sizeof(tcv));
  std::cin >> n >> m;
  while (m--)
  {
    std::cin >> l1 >> ch1 >> l2 >> ch2;
    c1 = (ch1 == 'C') ? 0 : 1;
    c2 = (ch2 == 'C') ? 0 : 1;
    e[l1 + c1 * n][l2 + c2 * n] = 1;
    e[l2 + (!c2) * n][l1 + (!c1) * n] = 1;
  }
  floyd();

  std::cin >> s;
  s = ' ' + s;
  fla = 0;
  for (int i = 1; i <= n; i++)
  {
    int mi = fla ? 1 : s[i] - 'a' + 1;
    if (check(i, mi, i + vc[mi] * n, fla))
      ans[i] = mi;
    else if (vc[mi] == vc[mi + 1] && check(i, mi + 1, i + vc[mi + 1] * n, 1))
      ans[i] = mi + 1, fla = 1;
    else if (nxt[mi] && check(i, nxt[mi], i + vc[nxt[mi]] * n, 1))
      ans[i] = nxt[mi], fla = 1;
    else if (nxu[mi] > nxt[mi] && nxu[mi] && check(i, nxu[mi], i + vc[nxu[mi]] * n, 1))
      ans[i] = nxu[mi], fla = 1;
    else
    {
      std::cout << -1 << '\n';
      return 0;
    }
  }

  for (int i = 1; i <= n; i++)
    putchar(static_cast<signed>(ans[i] + 'a' - 1));
  return 0;

}