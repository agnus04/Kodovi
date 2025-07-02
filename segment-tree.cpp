#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5;

int n, q, pot = 1;
int x[maxn];
int T[maxn * 4];

void update(int p, int v) {
	p += pot;
	T[p] = v;
	p /= 2;
	
	while(p >= 1) {
		T[p] = min(T[2 * p], T[2 * p + 1]);
		p /= 2;
	}
}

int query(int x, int l, int r, int a, int b) {
	if(r < a || b < l)
		return 1e9 + 1;
	if(a <= l && r <= b) 
		return T[x];
	
	int mid = (l + r) / 2;
	int L = query(2 * x, l, mid, a, b);
	int R = query(2 * x + 1, mid + 1, r, a, b);
	return min(L, R);
}

int main() {
	cin >> n >> q;
	for(int i = 0;i < n;i++)
		cin >> x[i];
	
	while(pot < n) pot *= 2;
	
	for(int i = 0;i < n;i++)
		T[i + pot] = x[i];
	for(int i = n;i < pot;i++)
		T[i + pot] = 1e9 + 1;
	for(int i = pot - 1;i >= 1;i--)
		T[i] = min(T[2 * i], T[2 * i + 1]);
	
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
			int ans = query(1, 0, pot - 1, a, b);
			cout << ans << "\n";
		}
	}
	return 0;
}

