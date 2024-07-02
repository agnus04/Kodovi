#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int n, m;
string s[101];

int get(int x, int y) {
	if(x < 0 || y < 0 || x >= n || y >= m) return 1;
	return s[x][y] == '.';	
}

int check(int x, int y) {
	if(s[x][y] != '*') return 0;
	int ret = 0;
	ret += get(x + 1, y);
	ret += get(x, y + 1);
	ret += get(x + 1, y + 1);
	return ret == 3;
}

int main() {
	cin >> n >> m;
	for(int i = 0;i < n;i++) cin >> s[i];
	
	int ans = 0;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < m;j++)
			if(check(i, j)) ans++;
	cout << ans << "\n";
	return 0;
}

