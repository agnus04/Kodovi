#include<bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n, q;
int x[maxn];
long long fwt[maxn];

void update(int p, long long v) {
	for(;p < maxn;p += p & -p) 
		fwt[p] += v;
}

long long query(int p) {
	long long sum = 0;
	for(;p > 0;p -= p & -p) 
		sum += fwt[p];
	return sum;	
}

int main() {
	cin >> n >> q;
	for(int i = 1;i <= n;i++)
		cin >> x[i];
	
	for(int i = 1;i <= n;i++)
		update(i, x[i]);
	
	for(int i = 0;i < q;i++) {
		int type;
		cin >> type;
		if(type == 1) {
			int k, u;
			cin >> k >> u;
			update(k, u - x[k]);
			x[k] = u;
		}
		if(type == 2) {
			int l, r;
			cin >> l >> r;
			long long ans = query(r) - query(l - 1);	
			cout << ans << "\n";
		}
	}
	return 0;
}

