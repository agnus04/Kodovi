#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int n, k, pot = 1;
int S[maxn], D[maxn];
int A[maxn];
int G[maxn * 2];
int T[maxn * 8];

int B[20], P[20];
int sz = 0;

void build() {
	while(pot < maxn * 2) pot *= 2;
	for(int i = 1;i < pot * 2;i++) T[i] = -1;
}

void update(int x, int v) {
	x += pot, T[x] = v;
	x >>= 1;
	while(x) T[x] = max(T[x * 2], T[x * 2 + 1]), x >>= 1;
}

int query(int x, int lo, int hi, int a, int b) {
	if(hi < a || lo > b) return -1;
	if(a <= lo && hi <= b) return T[x];
	int mid = (lo + hi) / 2;
	int L = query(x * 2, lo, mid, a, b);
	int R = query(x * 2 + 1, mid + 1, hi, a, b);
	return max(L, R);
}

void add(int x, int pos) {
	for(int i = 0;i < 20;i++) {
		if((x & (1 << i)) == 0) continue;
		if(B[i] == 0) {
			B[i] = x, P[i] = pos, sz++;
			return;
		}
		x ^= B[i];
	}
}

void solve(int x) {
	string ans;
	for(int i = 0;i < k;i++) ans += '0';
	for(int i = 0;i < 20;i++) {
		if((x & (1 << i)) == 0) continue;
		if(B[i] == 0) {
			ans = "nemoguce";
			break;
		}
		x ^= B[i], ans[P[i]] = '1';
	}
	printf("%s\n", ans.c_str());
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 0;i < n;i++)
		scanf("%d%d", S + i, D + i);
	for(int i = 0;i < k;i++) scanf("%d", A + i), A[i]--;
	
	vector<pair<ii, int>> v;
	for(int i = 0;i < n;i++) 
		v.pb({{S[i], D[i]}, i}), v.pb({{D[i], S[i]}, i + n});
	sort(all(v));

	build();
	vector<ii> U;
	for(int i = 0;i < n * 2;i++) {
		G[v[i].y] = query(1, 0, pot - 1, 1, v[i].x.y - 1) + 1;
		if(v[i].y < n) U.pb({v[i].x.y, G[v[i].y]});
		if(i + 1 < n * 2 && v[i].x.x != v[i + 1].x.x) {
			for(ii p : U) update(p.x, p.y);
			U.clear();
		}
	}
	
	int sum = 0;
	for(int i = 0;i < k;i++) 
		sum ^= G[A[i]], add(G[A[i]] ^ G[A[i] + n], i);
	
	solve(sum);
	return 0;
}
