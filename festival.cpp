#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int inf = 1e9;
const int maxn = 605;

int n, m1, m2;
int dist[maxn][maxn];
int vis[maxn];

int main() {
	scanf("%d%d%d", &n, &m1, &m2);
	for(int i = 0;i < n;i++) 
		for(int j = 0;j < n;j++) 
			if(i != j) dist[i][j] = inf;
			
	for(int i = 0;i < m1;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		dist[x][y] = min(dist[x][y], -1);
		dist[y][x] = min(dist[y][x], 1);
	}
	for(int i = 0;i < m2;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		dist[x][y] = min(dist[x][y], 0);
	}
	
	for(int k = 0;k < n;k++) 
		for(int i = 0;i < n;i++) 
			for(int j = 0;j < n;j++) 
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	
	int flag = 1;
	for(int i = 0;i < n;i++) 
		if(dist[i][i] < 0) flag = 0;
		
	if(flag == 0) printf("NIE\n");
	else {
		int ans = 0;
		for(int i = 0;i < n;i++) {
			if(vis[i]) continue;
			int maxi = 0;
			vector<int> v;
			for(int j = 0;j < n;j++) 
				if(dist[i][j] < inf / 2 && dist[j][i] < inf / 2)
					v.pb(j), vis[j] = 1;
			
			for(int j : v)
				for(int k : v)
					maxi = max(maxi, dist[j][k]);
			ans += maxi + 1;	
		}
		printf("%d\n", ans);
	}
	return 0;
}

