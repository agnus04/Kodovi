#include<bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n, q;
int p[maxn];
int fwt[3 * maxn];
int t[maxn];
int a[maxn];
int b[maxn];

void update(int p, int v) {
	for(;p < 3 * maxn;p += p & -p)
		fwt[p] += v;	
}	

int query(int p) {
	int res = 0;
	for(;p > 0;p -= p & -p)
		res += fwt[p];
	return res;	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	vector<int> v;
	cin >> n >> q;
	for(int i = 0;i < n;i++)
		cin >> p[i], v.push_back(p[i]);
	
	for(int i = 0;i < q;i++) {
		char c;
		cin >> c;
		cin >> a[i] >> b[i];
		if(c == '!') {
			t[i] = 1;
			a[i]--;
			v.push_back(b[i]);
		} else {
			t[i] = 2;
			a[i]--;
			v.push_back(a[i]);
			v.push_back(b[i]);	
		}
	}
	
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	
	map<int, int> pos;
	for(int i = 0;i < (int)v.size();i++)
		pos[v[i]] = i + 1;

	for(int i = 0;i < n;i++)
		p[i] = pos[p[i]];
	
	for(int i = 0;i < q;i++) {
		if(t[i] == 1) b[i] = pos[b[i]];
		else a[i] = pos[a[i]], b[i] = pos[b[i]];	
	}
	
	for(int i = 0;i < n;i++)
		update(p[i], 1);
	
	for(int i = 0;i < q;i++) {
		if(t[i] == 1) {
			update(p[a[i]], -1);
			update(b[i], 1);
			p[a[i]] = b[i];
		} else {
			int ans = query(b[i]) - query(a[i]);
			cout << ans << "\n";
		}
	}
	return 0;
}

