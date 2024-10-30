// Copyright (C) 2021 JacderZhang
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#ifndef SCANNER_H_
#define SCANNER_H_ 1
#include <stdio.h>
#include <stdlib.h>
class Scanner {
private:
  static const int BUFFER_SIZE = 1 << 18;
  char buff[BUFFER_SIZE];
  char *buffPos, *buffLim;
  FILE *file;

public:
  Scanner(FILE *file) {
    this->file = file;
    buffLim = buff + fread(buff, 1, BUFFER_SIZE, file);
    buffPos = buff; }

private:
  inline void flushBuff() {
    buffLim = buff + fread(buff, 1, BUFFER_SIZE, file);
    if (buffLim == buff) {
      *buffLim++ = '\n'; }
    buffPos = buff; }
  inline bool isWS(char t) {
    return t <= ' '; }
  inline bool isDig(char t) {
    return t >= '0' && t <= '9'; }
  inline void nextPos() {
    buffPos++;
    if (buffPos == buffLim) {
      flushBuff(); } }
public:
  inline char getchar() {
    char ch = *buffPos;
    nextPos();
    return ch; }
  inline void next(char* s) {
    while (isWS(*buffPos)) {
      nextPos(); }
    while (!isWS(*buffPos)) {
      *s = *buffPos;
      s++;
      nextPos(); }
    *s = '\0'; }
  inline void nextLine(char* s) {
    while (*buffPos != '\n') {
      nextPos(); }
    if (*buffPos == '\n') {
      nextPos(); }
    while (*buffPos != '\n') {
      *s++ = *buffPos;
      nextPos(); }
    *s = '\0'; }
  inline int nextInt() {
    while (!isDig(*buffPos) && *buffPos != '-') {
      nextPos(); }
    int sign = (*buffPos == '-') ? nextPos(), -1 : 1;
    int res = 0;
    while (isDig(*buffPos)) {
      res = res * 10 + *buffPos - '0';
      nextPos(); }
    return res * sign; }
  inline long long nextLong() {
    while (!isDig(*buffPos) && *buffPos != '-') {
      nextPos(); }
    long long sign = (*buffPos == '-') ? nextPos(), -1 : 1;
    long long res = 0;
    while (isDig(*buffPos)) {
      res = res * 10 + *buffPos - '0';
      nextPos(); }
    return res * sign; }
  inline int n() {
    while (*buffPos < '0' || *buffPos > '9') {
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff(); } }
    int res = 0;
    while (*buffPos >= '0' && *buffPos <= '9') {
      res = res * 10 + (*buffPos - '0');
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff(); } }
    return res; }
  inline long long nl() {
    while (*buffPos < '0' || *buffPos > '9') {
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff(); } }
    long long res = 0;
    while (*buffPos >= '0' && *buffPos <= '9') {
      res = res * 10 + (*buffPos - '0');
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff(); } }
    return res; }
  inline long long nlm(const int MOD) {
    while (*buffPos < '0' || *buffPos > '9') {
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff(); } }
    long long res = 0;
    while (*buffPos >= '0' && *buffPos <= '9') {
      res = (res * 10 + (*buffPos - '0')) % MOD;
      buffPos++;
      if (buffPos == buffLim) {
        flushBuff(); } }
    return res; }
  inline double nextDouble() {
    while (isWS(*buffPos)) {
      nextPos(); }
    int sign = (*buffPos == '-') ? nextPos(), -1 : 1;
    double res = 0;
    while (isDig(*buffPos)) {
      res = res * 10 + *buffPos - '0';
      nextPos(); }
    if (*buffPos == '.') {
      nextPos();
      double ep = 1;
      while (isDig(*buffPos)) {
        ep *= 0.1;
        res += ep * (*buffPos - '0');
        nextPos(); } }
    return sign * res; }
  inline char nextChar() {
    while (isWS(*buffPos))
      nextPos();
    char res = *buffPos;
    nextPos();
    return res; }
  ~Scanner() {
    fclose(file); } };
#ifndef SCANNER_H_CUSTOM
Scanner sc(stdin);
#endif
#endif /* SCANNER_H_ */
#ifndef LOG_H_
#define LOG_H_ 1

#include <iostream>
#include <utility>

template<class __TyFirst, class __TySecond>
std::ostream&
operator<<(std::ostream& out, const std::pair<__TyFirst, __TySecond>& o)
{
  out << "(" << o.first << "," << o.second << ")";
  return out;
}

#ifdef __LOCALE__

template<typename T>
void
__ses(T a)
{
  std::cout << a << " ";
}
template<typename T, typename... Args>
void
__ses(T a, Args... b)
{
  std::cout << a << " ";
  __ses(b...);
}
#define ses(...)                                                               \
  {                                                                            \
    std::cout << #__VA_ARGS__ << " = ";                                        \
    __ses(__VA_ARGS__);                                                        \
  }
#define see(...)                                                               \
  {                                                                            \
    ses(__VA_ARGS__);                                                          \
    std::cout << std::endl;                                                    \
  }
#define slog(format, ...) printf(format "\n", __VA_ARGS__)

static constexpr char __log_space[] = " ";
template<typename _ForwardIterator>
void
logArray(_ForwardIterator __begin,
         _ForwardIterator __end,
         const char* __sep = 0)
{
  if (__sep == 0) {
    __sep = __log_space;
  }
  while (__begin != __end) {
    std::cout << *__begin << *__sep;
    ++__begin;
  }
  std::cout << std::endl;
}

#else

#define see(...)
#define ses(...)
#define slog(format, ...)
template<typename _ForwardIterator>
void
logArray(_ForwardIterator __begin,
         _ForwardIterator __end,
         const char* __sep = 0)
{}

#endif

#endif /* LOG_H_ */
#ifndef RANGE_H_
#define RANGE_H_

#include <stdexcept>
#include <iterator>
#include <type_traits>

template <typename _IntType>
class range {
  static_assert(std::is_integral<_IntType>::value, "range object must have integral value type");

protected:
  class iterator : public std::iterator<std::input_iterator_tag, _IntType, _IntType, const _IntType*, _IntType> {
    _IntType val, step;

  public:
    using typename std::iterator<std::input_iterator_tag, _IntType, _IntType, const _IntType*, _IntType>::reference;
    explicit constexpr iterator(int val, int step) noexcept : val(val), step(step) {}
    constexpr iterator& operator++() noexcept { val += step; return *this; }
    constexpr iterator& operator++(int) noexcept { iterator ret = *this; val += step; return ret; }
    constexpr bool operator== (const iterator& rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!= (const iterator& rhs) const noexcept { return val != rhs.val; }
    constexpr reference operator*() const { return val; }
  };

public:
  typedef  _IntType value_type;
  const value_type _begin, _step, _end;

  explicit constexpr range(const value_type end) noexcept : _begin(0), _step(1), _end(end>0 ? end : 0) {}
  explicit constexpr range(const value_type begin, const value_type end) noexcept : 
    _begin(begin), _step(1), _end(end>begin ? end : begin) {}
  explicit constexpr range(const value_type begin, const value_type end, const value_type step) :
    _begin(begin), _step(step), _end((end-begin)/step>0 ? begin+(end-begin)/step*step : begin) {}
  constexpr iterator begin() const noexcept { return iterator(_begin, _step); }
  constexpr iterator end() const noexcept { return iterator(_end, _step); }
};

#endif
#ifndef BASE_H_
#define BASE_H_ 1

template<class T>
inline bool
checkMin(T& a, T b)
{
  return (a > b ? a = b, 1 : 0);
}
template<class T>
inline bool
checkMax(T& a, T b)
{
  return (a < b ? a = b, 1 : 0);
}

#endif /* BASE_H_ */

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#ifndef _BODY_MAIN
#define _BODY_MAIN 1

#ifndef CUSTOM_MAIN
void
preInit();
void
init();
void
solve();
int32_t
main()
{
  preInit();
#ifdef MULTIPLE_TEST_CASES_WITH_T
  int T;
#ifdef SCANNER_H_
  T = sc.nextInt();
#else
  scanf("%d", &T);
#endif /* SCANNER_H_ */
  while (T--) {
    init();
    solve();
  }
#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T
  while (1) {
    try {
      init();
    } catch (bool t) {
      return 0;
    }
    solve();
  }
#else
  init();
  solve();
#endif /* MULTIPLE_TEST_CASES_WITHOUT_T  */
#endif /* MULTIPLE_TEST_CASES_WITH_T */
  return 0;
}
#endif /* CUSTOM_MAIN */

#endif /* _BODY_MAIN */
// #define int long long

#define in :
/** My code begins here **/

constexpr int N = 502005;
constexpr int L = 1000;
constexpr int THR = 1000000000;
int bel[N], block_pos[N / L];

std::map<int,int> exist[N / L];
int block_add[N / L];
int a[N], n, q, block_cnt;

void inc(int pos, int val) {
  int b = bel[pos];
  if (a[pos] + block_add[b] > THR) { return; }
  int origin_value = a[pos];
  --exist[b][origin_value];
  a[pos] += val; 
  if (a[pos] + block_add[b] > THR) { return; }
  ++exist[b][a[pos]]; }

int search_forward(int b, int val) {
  if (block_add[b] > THR) { return -1; }
  val -= block_add[b];
  if (exist[b].find(val) == exist[b].end() || exist[b][val] == 0) { return -1; }
  for (int i in range(block_pos[b], block_pos[b+1])) {
    if (a[i] == val) { return i; } }
  return -1; }

int search_backward(int b, int val) {
  if (block_add[b] > THR) { return -1; }
  val -= block_add[b];
  if (exist[b].find(val) == exist[b].end() || exist[b][val] == 0) { return -1; }
  for (int i in range(block_pos[b+1]-1, block_pos[b]-1, -1)) {
    if (a[i] == val) { return i; } }
  return -1; }

void preInit() { } void init() {
  for (int i in range(0,N,L)) {
    block_pos[i / L] = i;
    for (int j in range(i,i+L)) { bel[j] = i / L; } }
  n = sc.n(); q = sc.n();
  for (int i in range(n)) { a[i] = sc.n(); }
  for (int i in range(n)) { ++exist[bel[i]][a[i]]; }
  block_cnt = bel[n-1] + 1;
} void solve() {
  while (q--) {
    int opt = sc.n();
    if (opt == 1) {
      int l=sc.n()-1, r=sc.n()-1, k=sc.n();
      int lb = bel[l], rb = bel[r];
      if (lb == rb) {
        for (int i in range(l,r+1)) { inc(i,k); } }
      else {
        for (int i in range(lb+1, rb)) if (block_add[i] <= THR) { block_add[i] += k; }
        for (int i in range(l, block_pos[lb+1])) { inc(i, k); }
        for (int i in range(block_pos[rb], r+1)) { inc(i, k); } } }
    else {
      int val = sc.n();
      int min = -1;
      for (int i in range(block_cnt)) {
        int t = search_forward(i, val); 
        if (t != -1) { min = t; break; } }
      if (min == -1) { puts("-1"); continue; }
      int max = -1;
      for (int i in range(block_cnt-1, -1, -1)) {
        int t = search_backward(i, val);
        if (t != -1) { max = t; break; } }
      printf("%d\n", max - min); }
  }
}