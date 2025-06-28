#include<bits/stdc++.h>

using namespace std;

struct UnionFind {
	vector<int> par;
	vector<int> rank;
	
	UnionFind(int n) {
		for(int i = 0;i < n;i++)
			par.push_back(i), rank.push_back(1);
	}
	
	int find(int x) {
		if(par[x] == x)
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

int n, m;

int main() {
	cin >> n >> m;
	UnionFind UF(n);
	for(int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		UF.merge(a, b);	
	}
	
	vector<int> rep;
	for(int i = 0;i < n;i++)
		if(UF.par[i] == i)
			rep.push_back(i);
	
	cout << rep.size() - 1 << "\n";
	for(int i = 1;i < (int)rep.size();i++)
		cout << rep[i - 1] + 1 << " " << rep[i] + 1 << "\n";
	return 0;
}

