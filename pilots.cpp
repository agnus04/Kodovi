#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 3e6 + 5;

struct mono {
	queue<int> q;
	deque<int> dq;
	void add(int x) {
		q.push(x);
		while(dq.size() && dq.back() < x) dq.pop_back();
		dq.pb(x);
	}
	void remove() {
		int x = q.front();q.pop();
		if(dq.front() == x) dq.pop_front();	
	}
	int max() {
		return dq.front();	
	}
};

int n, t;
int A[maxn];

int main() {
	scanf("%d%d", &t, &n);
	for(int i = 0;i < n;i++) 
		scanf("%d", A + i);
	
	int hi = 0, ans = -1;
	mono Q1, Q2;
	for(int i = 0;i < n;i++) {
		if(i == hi) Q1.add(A[hi]), Q2.add(-A[hi]), hi++;
		int sol = Q1.max() + Q2.max();
		if(sol <= t) ans = max(ans, hi - i);
		while(hi < n) {
			Q1.add(A[hi]), Q2.add(-A[hi]);
			sol = Q1.max() + Q2.max();
			hi++;
			if(sol > t) break;
			ans = max(ans, hi - i);
		}
		Q1.remove(), Q2.remove();
	}
	printf("%d\n", ans);
	return 0;
}

