#include<bits/stdc++.h>

using namespace std;

const int maxn = 205;

int R, G, B;
int r[maxn];
int g[maxn];
int b[maxn];
long long dp[maxn][maxn][maxn];

long long rek(int x, int y, int z) {
	if(R + G + B - (x + y + z) < 2) return 0;
	if(dp[x][y][z] != -1)
		return dp[x][y][z];
	
	long long ret = 0;
	if(x + 1 <= R && y + 1 <= G)
		ret = max(ret, rek(x + 1, y + 1, z) + r[x + 1] * g[y + 1]);
	if(x + 1 <= R && z + 1 <= B)
		ret = max(ret, rek(x + 1, y, z + 1) + r[x + 1] * b[z + 1]);
	if(y + 1 <= G && z + 1 <= B)
		ret = max(ret, rek(x, y + 1, z + 1) + g[y + 1] * b[z + 1]);
	
	return dp[x][y][z] = ret;
}

int main() {
	cin >> R >> G >> B;
	for(int i = 1;i <= R;i++)
		cin >> r[i];
	for(int i = 1;i <= G;i++)
		cin >> g[i];
	for(int i = 1;i <= B;i++)
		cin >> b[i];
	
	memset(dp, -1, sizeof dp);
	sort(r + 1, r + R + 1);
	sort(g + 1, g + G + 1);
	sort(b + 1, b + B + 1);
	reverse(r + 1, r + R + 1);
	reverse(g + 1, g + G + 1);
	reverse(b + 1, b + B + 1);
	cout << rek(0, 0, 0) << "\n";
	return 0;
}


