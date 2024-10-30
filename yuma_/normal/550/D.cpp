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
#include<memory>

#pragma warning(disable:4996)
using namespace std;
using ld = long double;
template<class T>
using Table = vector<vector<T>>;
const ld eps=1e-9;
using ll=long long ;
const ll mod=1e9+7;
using Graph=vector<vector<int>>;
	
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
//1. mask
	// 	a. i==0
	// 	for(int i=mask; i>0; i=(i-1)&mask) {
	// 	}

	// b. i==0
	// 	for(int i=mask; i>=0; i--) {
	// 		i&=mask;
	// 	}
// 2. mask

// mask

// 	for(int i=mask; i<(1<<n); i=(i+1)|mask) {
// 	}

	
using ll = long long int;
int H,W;
bool ch(int x,int y){
    return x>=0&&x<W&&y>=0&&y<H;
}

vector<int>ls,rs;
vector<map<int,int>>mp;
void dfs(int now,const vector<vector<int>>&tos,int &id,const string&st,int dep){
    ls[now]=id;
    int kk=st[now]-'a';
    
    for(auto to:tos[now]){
        dfs(to,tos,id,st,dep+1);
    }
    id++;

    auto it=mp[dep].lower_bound(id);
    if(it==mp[dep].begin()){
        mp[dep][id]=1<<kk;
    }else{
        mp[dep][id]=(prev(it)->second)^(1<<kk);
    }
    rs[now]=id;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie();
    int K;cin>>K;
    int N;
    vector<pair<int,int>>ps;
    if(K%2==1){
        ps.emplace_back(0,1);
        for(int x=0;x<2;++x){
            for(int i=0;i<K-1;++i){
                ps.emplace_back(x,2+i*2+x);

                for(int j=0;j<K-1;++j){
                    ps.emplace_back(i*2+2+x,2*(j+(K-1))+2+x);
                }
            }
            for(int j=0;j<K-1;j+=2){
                int a=j+(K-1);
                int b=a+1;
                if(j==K-2)b-=(K-1);
                ps.emplace_back(2*a+2+x,2*b+2+x);
            }
        }
        
        cout<<"YES"<<endl;
        cout<<4*K-2<<' '<<ps.size()<<endl;
        for(auto p:ps){
            cout<<p.first+1<<' '<<p.second+1<<endl;
        }
    }else{
        cout<<"NO"<<endl;
    }
    
	return 0;
}