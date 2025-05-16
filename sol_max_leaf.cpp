#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5;

int n;
vector<ii> d;
int out[maxn];
int nxt[maxn];
int lst[maxn];
vector<int> adj[maxn];
map<int, vector<int>> triag[maxn];
map<int, int> dp[2][2][maxn];
map<int, int> vis[2][2][maxn];

int cmp(ii a, ii b) {
	int l1 = min(a.y - a.x, n - a.y + a.x);
	int l2 = min(b.y - b.x, n - b.y + b.x);
	if(l1 != l2) return l1 < l2;
	return a < b;
}

void add_triangle(int x, int y, int z) {
	triag[x][y].pb(z), triag[y][x].pb(z);
	triag[x][z].pb(y), triag[z][x].pb(y);
	triag[y][z].pb(x), triag[z][y].pb(x);
}

int solve(int lo, int hi, int flag_lo, int flag_hi) {
	if(vis[flag_lo][flag_hi][lo][hi])
		return dp[flag_lo][flag_hi][lo][hi];
	if(hi - lo == 1) return 0;

	int x = triag[lo][hi][0];
	if(!(lo < x && x < hi)) x = triag[lo][hi][1];
	int ret = solve(lo, x, flag_lo, 0) + solve(x, hi, 0, flag_hi);
	
	int flag = 1;
	if(x - lo > 1 && flag_lo) flag = 0;
	if(hi - x > 1 && flag_hi) flag = 0;
	if(flag)
		ret = max(ret, solve(lo, x, flag_lo, 1) + solve(x, hi, 1, flag_hi) + 1);

	vis[flag_lo][flag_hi][lo][hi] = 1;
	return dp[flag_lo][flag_hi][lo][hi] = ret;
}

int main(void) {
    auto start = chrono::high_resolution_clock::now();
    scanf("%d", &n);
	for(int i = 3;i < n;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		if(x > y) swap(x, y);
		d.pb({x, y});
	}

	sort(all(d), cmp);
	for(int i = 0;i < n;i++) {
		nxt[i] = (i + 1) % n;
		lst[i] = (i - 1 + n) % n;
	}

	int N = 0;
	for(auto [x, y] : d) {
		int z;
		if(nxt[nxt[x]] == y)
			z = nxt[x], nxt[x] = y, lst[y] = x;
		 else z = lst[x], lst[x] = y, nxt[y] = x;

		add_triangle(x, y, z);
		out[z] = 1, N++;
	}

	vector<int> t;
	for(int i = 0;i < n;i++)
		if(out[i] == 0) t.pb(i);
    add_triangle(t[0], t[1], t[2]);

	int ans = 0;
	for(int i = 0;i < 2;i++)
		for(int j = 0;j < 2;j++)
			ans = max(ans, solve(0, n - 1, i, j) + i + j);
    //freopen("out.txt", "a", stdout);
	cout << ans << "\n";
	//fclose(stdout);
    auto end = chrono::high_resolution_clock::now();
    //cout << (double)chrono::duration_cast<chrono::nanoseconds>(end-start).count()/1e9 << "s\n";
    return 0;
}