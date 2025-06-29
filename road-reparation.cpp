#include<bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n, m;

struct UnionFind {
	vector<int> par, rank;
	
	UnionFind(int n) {
		for(int i = 0;i < n;i++)
			par.push_back(i), rank.push_back(1);
	}
	
	int find(int x) {
		if(x == par[x])
			return x;
		return find(par[x]);
	}
	
	int merge(int x, int y) {
		x = find(x), y = find(y);
		if(x == y) return 0;
		if(rank[x] < rank[y]) swap(x, y);
		par[y] = x;
		if(rank[x] == rank[y]) rank[x]++;
		return 1;	
	}
};

int main() {
	cin >> n >> m;
	UnionFind UF(n);
	vector<pair<int, pair<int, int>>> E;
	for(int i = 0;i < m;i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		E.push_back({c, {a, b}});
	}	
	sort(E.begin(), E.end());
	
	long long ans = 0;
	int broj_bridova = 0;
	for(int i = 0;i < m;i++) {
		int c = E[i].first;
		int a = E[i].second.first;
		int b = E[i].second.second;
		if(UF.merge(a, b)) {
			ans += (long long)c;	
			broj_bridova++;
		}
	}
	
	if(broj_bridova != n - 1) {
		cout << "IMPOSSIBLE\n";	
	} else {
		cout << ans << "\n";
	}
	return 0;
}

