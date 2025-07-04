#include<bits/stdc++.h>

using namespace std;

typedef pair<long long, long long> pll;

const int maxn = 2e5 + 5;

int n, q, pot = 1;
int x[maxn];
pll T[maxn * 4];

pll combine(pll A, pll B) {
	pll ret = {0, 0};
	ret.second = A.second + B.second;
	ret.first = max(A.first, A.second + B.first);
	return ret;	
}

void update(int p, int v) {
	p += pot;	
	T[p] = {max(0, v), v};
	p /= 2;
	
	while(p >= 1) {
		T[p] = combine(T[p * 2], T[p * 2 + 1]);	
		p /= 2;
	}
}

pll query(int x, int l, int r, int a, int b) {
	if(r < a || b < l) return {0, 0};
	if(a <= l && r <= b) return T[x];
	
	int mid = (l + r) / 2;
	pll L = query(x * 2, l, mid, a, b);
	pll R = query(x * 2 + 1, mid + 1, r, a, b);
	return combine(L, R);
}

int main() {
	cin >> n >> q;
	for(int i = 0;i < n;i++)
		cin >> x[i];
	
	while(pot < n) pot *= 2;
	
	for(int i = 0;i < n;i++)
		update(i, x[i]);
	
	for(int i = 0;i < q;i++) {
		int t;
		cin >> t;
		if(t == 1) {
			int k, u;
			cin >> k >> u;
			k--;
			update(k, u);
		}
		if(t == 2) {
			int a, b;
			cin >> a >> b;
			a--, b--;
			pll ans = query(1, 0, pot - 1, a, b);
			cout << ans.first << "\n";	
		}
	}
	return 0;
}

