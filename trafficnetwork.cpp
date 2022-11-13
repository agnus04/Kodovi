#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 3e5 + 5;

int n, m, A, B;
int X[maxn], Y[maxn];
vector<int> adj[2][maxn], G[maxn];
int comp[maxn];
int dp1[maxn], dp2[maxn];
int deg[maxn];

void add_edge(int x, int y, int flag) {
	adj[0][x].pb(y);
	adj[1][y].pb(x);
	if(flag) adj[0][y].pb(x), adj[1][x].pb(y);
}

int C = 1;
vector<int> st;

void dfs(int x, int flag) {
	if(comp[x]) return;
	comp[x] = C;
	for(int y : adj[flag][x]) dfs(y, flag);
	if(flag == 0) st.pb(x);
}

int main() {
	scanf("%d%d%d%d", &n, &m, &A, &B);
	for(int i = 0;i < n;i++) 
		scanf("%d%d", X + i, Y + i);
	for(int i = 0;i < m;i++) {
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		x--, y--, k--;
		add_edge(x, y, k);
	}
	for(int i = 0;i < n;i++) dp1[i] = 1e9 + 1, dp2[i] = -1;
	
	for(int i = 0;i < n;i++) 
		if(comp[i] == 0 && X[i] == 0) dfs(i, 0);
	
	memset(comp, 0, sizeof comp);
	vector<int> v = st;
	while(st.size()) {
		int x = st.back();
		st.pop_back();
		if(comp[x] == 0) dfs(x, 1), C++;
	}
	
	for(int i : v) 
		for(int j : adj[0][i]) 
			if(comp[i] != comp[j]) G[comp[i]].pb(comp[j]), deg[comp[j]]++;
	
	for(int i : v) 
		if(X[i] == A) 
			dp1[comp[i]] = min(dp1[comp[i]], Y[i]), dp2[comp[i]] = max(dp2[comp[i]], Y[i]);
	
	queue<int> q;
	vector<int> V;
	for(int i = 1;i < C;i++) 
		if(deg[i] == 0) q.push(i);
	
	while(q.size()) {
		int x = q.front();q.pop();
		V.pb(x);
		for(int y : G[x]) {
			deg[y]--;
			if(deg[y] == 0) q.push(y);
		}
	}
	
	reverse(all(V));
	for(int i : V) 
		for(int j : G[i])
			dp1[i] = min(dp1[i], dp1[j]), dp2[i] = max(dp2[i], dp2[j]);
	
	vector<int> v1;
	for(int i : v) if(X[i] == A) v1.pb(Y[i]);
	sort(all(v1));
	
	vector<ii> ans;
	for(int i : v) {
		if(X[i] == 0) {
			int x = comp[i];
			if(dp2[x] == -1) {ans.pb({-Y[i], 0});continue;}
			int lo = lower_bound(all(v1), dp1[x]) - v1.begin();
			int hi = lower_bound(all(v1), dp2[x]) - v1.begin();
			ans.pb({-Y[i], hi - lo + 1});
		}
	}
	
	sort(all(ans));
	for(ii p : ans) printf("%d\n", p.y);
	return 0;
}
