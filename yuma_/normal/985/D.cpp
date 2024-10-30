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
using ll=long long ;

int main() {
	ios::sync_with_stdio(false);
	ll A,H;cin>>A>>H;
	ll ng=0;
	ll ok=2e9;

	while(ng+1!=ok){
		ll amid((ng+ok)/2);
		ll ax=0;
		if(amid<=H){
			ax=amid*(amid+1)/2;
		}else{
			ll ah=H+(amid-H)/2;

			if((amid-H)%2){
				ax=ah*(ah+1)/2+(ah+H)*(ah-H+1)/2;
			}else{
				ax=ah*(ah+1)/2+(ah+H-1)*(ah-H)/2;
			}
			/*
			H
			H+1
			H+2
			H+1
			H
			H-1
			.
			.
			.
			1
			*/
		}
		//WHATS(amid)
		//WHATS(ax)
		bool aok=ax>=A;
		
		if(aok)ok=amid;
		else ng=amid;
	}
	cout<<ok<<endl;
	return 0;
}