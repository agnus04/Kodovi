#include<bits/stdc++.h>

using namespace std;

vector<int> par;
vector<int> rnk;

int find(int x) {
	if(par[x] == x)
		return x;
	return find(par[x]);	
}

int merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return 0;
	if(rnk[x] < rnk[y]) swap(x, y);
	par[y] = x;
	if(rnk[x] == rnk[y]) rnk[x]++;
	return 1;		
}

int n, m;

int main() {
	cin >> n >> m;
	for(int i = 0;i < n;i++)
		par.push_back(i), rnk.push_back(1);
		
	for(int i = 0;i < m;i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		merge(a, b);	
	}
	
	vector<int> rep;
	for(int i = 0;i < n;i++)
		if(par[i] == i)
			rep.push_back(i);
	
	cout << rep.size() - 1 << "\n";
	for(int i = 1;i < (int)rep.size();i++)
		cout << rep[i - 1] + 1 << " " << rep[i] + 1 << "\n";
	return 0;
}

