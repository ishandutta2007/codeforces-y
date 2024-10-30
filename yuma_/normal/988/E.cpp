#include "bits/stdc++.h"
#include<unordered_map>
#include<unordered_set>
#pragma warning(disable:4996)
using namespace std;
using ld = long double;
const ld eps = 1e-9;


namespace cent {

	struct Edge {
		int src;
		int dst;
		long long int cost;
	};
	using Graph = vector<vector<Edge>>;

	class Centroid {
	private:
		int dfs(const Graph&g, const int now, const int from, vector<int>&ch_nums, const vector<int>&oks) {
			int sum = 1;
			for (auto &&e : g[now]) {
				if (e.dst == from || oks[e.dst] != -1)continue;
				else {
					sum += dfs(g, e.dst, e.src, ch_nums, oks);
				}
			}
			return ch_nums[now] = sum;
		}

		int find_centroid(const int asize, const vector<vector<Edge>>&graph, const int pre_root, const int pre_from, const vector<int>&ch_nums, const vector<int>&oks) {
			for (auto&& e : graph[pre_root]) {
				if (e.dst == pre_from)continue;
				if (oks[e.dst] != -1)continue;
				if (ch_nums[e.dst]>asize / 2)return find_centroid(asize, graph, e.dst, e.src, ch_nums, oks);
			}
			return pre_root;
		}

		void dfs2(const Graph&g, const int root,const int now, const int from, const vector<int>&oks,int depth) {
			mp[make_pair(root,now)]=depth;
			for (auto &&e : g[now]) {
				if (e.dst == from || oks[e.dst] != -1)continue;
				else {
					dfs2(g,root,e.dst,e.src,oks,depth+1);
				}
			}
		};


		void cent(const vector<vector<Edge>>&graph, vector<int>&oks, const int root, const int from, vector<vector<int>>&centroid_edges, int& fst_centroid, int depth, vector<int>&ch_nums) {
			dfs(graph, root, from, ch_nums, oks);

			int cent_id = find_centroid(ch_nums[root], graph, root, from, ch_nums, oks);


			dfs2(graph,cent_id,cent_id,-1,oks,0);
			lens1[cent_id][make_pair(0,0)]--;
			lens2[cent_id][0]--;


			oks[cent_id] = depth;

			//for (auto&& e : graph[cent_id]) {
			//	if (e.dst == from)continue;
			//	if (oks[e.dst] != -1)continue;

			//	dfs2(graph, e.dst, e.dst, e.src, oks,e.cost%mod,e.cost%mod,1);

			//	for (auto&& l1 : lens1[e.dst]) {
			//		int keta = l1.first.second;
			//		long long int num = l1.first.first;

			//		long long int need = (mod - num) / mod_pow(10, keta);
			//		need%=mod;
			//		auto it = lens2[e.dst].find(need);
			//		if (it != lens2[e.dst].end()) {
			//			ans -= l1.second*it->second;
			//		}
			//	}
			//	lens1[e.dst].clear();
			//	lens2[e.dst].clear();
			//}

			if (from != -1) {
				centroid_edges[from].push_back(cent_id);
			}
			else {
				fst_centroid = cent_id;
			}
			for (auto&& e : graph[cent_id]) {
				if (e.dst == from)continue;
				if (oks[e.dst] != -1)continue;
				cent(graph, oks, e.dst, e.src, centroid_edges, fst_centroid, depth + 1, ch_nums);
			}
		}

	public:

		map<pair<int,int>,int>mp;

		vector<map<pair<long long int,int>, long long int>>lens1;
		vector<map<long long int, long long int>>lens2;
		vector<vector<int>> centroid_graph;
		vector<int>ts;
		vector<int>parents;
		vector<int>oks;
		vector<int>anss;

		//fst:root  snd:centroid_graph
		void init(const Graph&g) {
			lens1.resize(g.size());
			lens2.resize(g.size());
			oks = vector<int>(g.size(), -1);
			int root = -1;
			centroid_graph.resize(g.size());
			parents = vector<int>(g.size(), -1);
			ts=vector<int>(g.size(),-1);
			anss=vector<int>(g.size(),100000);

			vector<int>ch_nums(g.size());
			cent(g, oks, 0, -1, centroid_graph, root, 0, ch_nums);

			for (int i = 0; i < centroid_graph.size(); ++i) {
				for (auto&& e : centroid_graph[i]) {
					parents[e] = i;
				}
			}
			return ;
		}
	}centroid;


	void addEdge(Graph& g, int a, int b, long long int c) {
		g[a].push_back(Edge{ a,b,c });
		g[b].push_back(Edge{ b,a,c });
	}
}




int main()
{
	string st;cin>>st;
	int ans=1000;
	if (st.size() == 1) {
	}
	else {
		vector<int>v(st.size());
		for (int i = 0; i < st.size(); ++i) {
			v[i]=st[i]-'0';
		}
		vector<vector<int>>t{ {2,5},{5,0},{7,5},{0,0} };
		for (int i = 0; i < 4; ++i) {
			for (int x = 0; x < st.size(); ++x) {
				for (int y = 0; y < st.size(); ++y) {
					if(x==y)continue;
					if (v[x] == t[i][0] && v[y] == t[i][1]) {
						int xdis=((st.size()-2)-x);
						int ydis=((st.size()-1)-y);

						int r_zero_num=0;
						if (x == 0) {
							int n(1);
							while (n != st.size()) {
								if(v[n]==0)r_zero_num++;
								else break;
								n++;
							}
							if(n-1==y)r_zero_num--;
						}
						if (y == 0) {
							int n(1);
							while (n != st.size()) {
								if (v[n] == 0)r_zero_num++;
								else break;
								n++;
							}
							if(n-1==x)r_zero_num--;
						}
						int nans;
						if(xdis==-1)nans=ydis;
						if(x<y)nans=xdis+ydis;
						else nans=xdis+ydis+1;

						nans+=r_zero_num;
						ans=min(ans,nans);
					}
				}
			}
		}
	}
	if(ans==1000)ans=-1;
	cout<<ans<<endl;
	return 0;
}