#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5;

int n, m, C = 1;
vector<int> adj[2][maxn], G[maxn];
int vis[maxn];
int deg[maxn];
int pos[maxn];
string mat[105];

void add_edge(int x, int y) {
	adj[0][x ^ 1].pb(y);
	adj[1][y].pb(x ^ 1);
	adj[0][y ^ 1].pb(x);
	adj[1][x].pb(y ^ 1);	
}

void add_n(int x, int y) {
	vector<int> v, h;
	for(int i = x - 1;i >= 0;i--) {
		if(mat[i][y] == '#') break;
		if(mat[i][y] == 'T') {v.pb((i * m + y) * 2 + 1);break;}
	}
	for(int i = x + 1;i < n;i++) {
		if(mat[i][y] == '#') break;
		if(mat[i][y] == 'T') {v.pb((i * m + y) * 2);break;}
	}
	for(int i = y - 1;i >= 0;i--) {
		if(mat[x][i] == '#') break;
		if(mat[x][i] == 'T') {h.pb(((x + n) * m + i) * 2 + 1);break;}
	}
	for(int i = y + 1;i < m;i++) {
		if(mat[x][i] == '#') break;
		if(mat[x][i] == 'T') {h.pb(((x + n) * m + i) * 2);break;}
	}
	if(v.size() > 1) v.clear();
	if(h.size() > 1) h.clear();
	vector<int> V;
	for(int i : v) V.pb(i);
	for(int i : h) V.pb(i);
	if(V.size() == 0) return;
	if(V.size() == 1) V.pb(V[0]);
	add_edge(V[0], V[1]);
}

void add_T(int x, int y) {
	vector<int> v;
	for(int i = x - 1;i >= 0;i--) {
		if(mat[i][y] == '#') break;
		if(mat[i][y] == 'T') {v.pb((x * m + y) * 2 + 1);break;}
	}
	for(int i = x + 1;i < n;i++) {
		if(mat[i][y] == '#') break;
		if(mat[i][y] == 'T') {v.pb((x * m + y) * 2);break;}
	}
	for(int i = y - 1;i >= 0;i--) {
		if(mat[x][i] == '#') break;
		if(mat[x][i] == 'T') {v.pb(((x + n) * m + y) * 2 + 1);break;}
	}
	for(int i = y + 1;i < m;i++) {
		if(mat[x][i] == '#') break;
		if(mat[x][i] == 'T') {v.pb(((x + n) * m + y) * 2);break;}
	}
	
	for(int i : v) add_edge(i, i);
}

vector<int> topo;
void dfs(int x, int f) {
	if(vis[x]) return;
	vis[x] = C;
	for(int y : adj[f][x]) dfs(y, f);
	if(f == 0) topo.pb(x);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0;i < n;i++) cin >> mat[i];

	for(int i = 0;i < n;i++) 
		for(int j = 0;j < m;j++) {
			if(mat[i][j] == 'n') add_n(i, j);
			if(mat[i][j] == 'T') add_T(i, j);
		}
	
	for(int i = 0;i < maxn;i++) dfs(i, 0);
	memset(vis, 0, sizeof vis);
	reverse(all(topo));
	for(int i : topo) {
		if(vis[i]) continue;
		C++, dfs(i, 1);	
	}
	
	for(int i = 0;i < maxn;i++) 
		for(int j : adj[0][i]) 
			if(vis[i] != vis[j]) 
				G[vis[i]].pb(vis[j]), deg[vis[j]]++;
	
	queue<int> q;
	for(int i = 0;i < maxn;i++)
		if(deg[i] == 0) q.push(i);
	
	int cnt = 1;
	while(q.size()) {
		int x = q.front();q.pop();
		pos[x] = cnt++;
		for(int y : G[x]) {
			deg[y]--;
			if(deg[y] == 0) q.push(y);
		}
	}
	
	for(int i = 0;i < n * m;i++) {
		int x = i / m;
		int y = i % m;
		if(mat[x][y] != 'T') continue;
		int d = 1, r = 1;
		if(pos[vis[i * 2 + 1]] < pos[vis[i * 2]]) d = 0;
		if(pos[vis[(i + n * m) * 2 + 1]] < pos[vis[(i + n * m) * 2]]) r = 0;
		if(r == 0 && d == 0) mat[x][y] = '4';
		if(r == 0 && d == 1) mat[x][y] = '1';
		if(r == 1 && d == 0) mat[x][y] = '3';
		if(r == 1 && d == 1) mat[x][y] = '2';		
	}
	
	for(int i = 0;i < n;i++) 
		printf("%s\n", mat[i].c_str());
	return 0;
}

