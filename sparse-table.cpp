#include<bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n, q;
int x[maxn];
int pot[maxn]; //pot[len] = k ako 2^k <= len, ali 2^(k+1) > len
int st[maxn][20];  //st[i][j] - min na segmentu [i, i + 2^j - 1]

int main() {
	cin >> n >> q;
	for(int i = 0;i < n;i++)
		cin >> x[i];
	
	for(int i = 0;i < n;i++)
		st[i][0] = x[i];
	
	for(int j = 1;j < 20;j++) 
		for(int i = 0;i < n;i++) 
			if(i + (1 << j) - 1 < n) //(1 << j) = 2^j
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	
	pot[1] = 0;
	for(int i = 2;i <= n;i++) {
		pot[i] = pot[i - 1];
		if((1 << (pot[i] + 1)) <= i) pot[i]++;
	}
	
	for(int i = 0;i < q;i++) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		int len = r - l + 1;
		int ans = min(st[l][pot[len]], st[r - (1 << pot[len]) + 1][pot[len]]);
		cout << ans << "\n";
	}
	return 0;
}
