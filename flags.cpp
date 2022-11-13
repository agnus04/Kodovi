#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5;

int n, C = 1, D;
int X[maxn];
int N[maxn];
int comp[maxn];
vector<int> st;
set<ii> S;

void dfs(int x) {
	S.erase({X[N[x]], x});
	comp[x] = C;
	int flag = 1;
	while(flag) {
		if(S.size() == 0) {flag = 0;continue;}
		auto it = S.lower_bound({X[x] - D + 1, -1});
		if(it->y == N[x]) it++;
		if(it == S.end()) {flag = 0;continue;}
		if(it->x >= X[x] + D) {flag = 0;continue;}
		dfs(it->y);
	}
	st.pb(x);
}

void rdfs(int x) {
	S.erase({X[x], x});
	comp[x] = C;
	int flag = 1;
	while(flag) {
		if(S.size() == 0) {flag = 0;continue;}
		
		auto it = S.lower_bound({X[N[x]] - D + 1, -1});
		if(it->y == N[x]) it++;
		if(it == S.end()) {flag = 0;continue;}
		if(it->x >= X[N[x]] + D) {flag = 0;continue;}
		rdfs(it->y);
	}
}
int check(int d) {
	D = d, C = 1, S.clear();
	for(int i = 0;i < n * 2;i++) S.insert({X[i], N[i]});
	
	memset(comp, 0, sizeof comp);
	while(S.size()) {
		ii p = *S.begin();
		dfs(p.y);
	}
	
	memset(comp, 0, sizeof comp);
	for(int i = 0;i < n * 2;i++) S.insert({X[i], i});
	while(st.size()) {
		int x = st.back();st.pop_back();
		if(comp[x] == 0) rdfs(x), C++;
	}
	
	for(int i = 0;i < n;i++) 
		if(comp[i] == comp[N[i]]) return 0;
	return 1;
}

int main() {
	scanf("%d", &n);
	for(int i = 0;i < n;i++) 
		N[i] = i + n, N[i + n] = i;
	for(int i = 0;i < n;i++) 
		scanf("%d %d", X + i, X + n + i);
	
	
	int lo = 0, hi = 1e9, ans = -1;
	while(lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		int flag = check(mid);
		if(flag) ans = mid, lo = mid + 1;
		else hi = mid - 1;
	}
	assert(ans != -1);
	printf("%d\n", ans);
	return 0;
}
