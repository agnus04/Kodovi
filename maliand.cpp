#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 5e5 + 5;

int n, k, l;
int A[maxn];

int main() {
	scanf("%d%d%d", &n, &k, &l);
	
	ll ans = (ll)k * l + n - 1;
	ans /= n;
	printf("%lld\n", ans);
	for(int i = 0;i < k;i++) printf("1");
	for(int i = k;i < n;i++) printf("0");
	printf("\n");
	int x = 0;
	for(int i = 0;i < l;i++) {
		if(A[x]) x = (x + 1) % n;
		A[x] = 1, x += k;
		x %= n;
	}
	for(int i = 0;i < n;i++) printf("%d", A[i]);
	printf("\n");
	return 0;
}

