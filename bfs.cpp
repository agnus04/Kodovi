#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int n, m;
vector<int> adj[maxn];
int dist[maxn];
int pret[maxn];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0;i < m;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		adj[x].pb(y);
		adj[y].pb(x);	
	}
	for(int i = 0;i < n;i++) dist[i] = 1e9;
	
	queue<int> q;
	dist[0] = 0;
	q.push(0);
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(int y : adj[x]) {
			if(dist[y] == 1e9)
				dist[y] = dist[x] + 1, pret[y] = x, q.push(y);
		}
	}
	
	if(dist[n - 1] == 1e9) {
		printf("IMPOSSIBLE\n");
		return 0;
	}
	
	vector<int> ans;
	int x = n - 1;
	while(x) 
		ans.pb(x), x = pret[x];
	ans.pb(0);
	reverse(all(ans));
	
	printf("%d\n", (int)ans.size());
	for(int i : ans)
		printf("%d ", i + 1);
	printf("\n");
	return 0;
}


