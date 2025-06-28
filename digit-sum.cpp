#include<bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 5;
const int MOD = 1e9 + 7;

string k;
int d, n;
int dp[maxn][105][2];

int rek(int pozicija, int ostatak, int zastavica) {
	if(pozicija == n) {
		if(ostatak == 0) return 1;
		return 0;	
	}
	if(dp[pozicija][ostatak][zastavica] != -1)
		return dp[pozicija][ostatak][zastavica];
	
	int ret = 0;
	if(zastavica == 1) {
		for(int zn = 0;zn < 10;zn++) {
			ret += rek(pozicija + 1, (ostatak + zn) % d, 1);
			ret %= MOD;
		}
	} else {
		for(int zn = 0;zn < (k[pozicija] - '0');zn++) {
			ret += rek(pozicija + 1, (ostatak + zn) % d, 1);
			ret %= MOD;
		}
		ret += rek(pozicija + 1, (ostatak + k[pozicija] - '0') % d, 0);
		ret %= MOD;
	}
	return dp[pozicija][ostatak][zastavica] = ret;
}

int main() {
	cin >> k >> d;
	n = k.size();
	memset(dp, -1, sizeof dp);
	int ans = rek(0, 0, 0) - 1;
	ans = (ans + MOD) % MOD;
	cout << ans << "\n";
	return 0;
}
	

