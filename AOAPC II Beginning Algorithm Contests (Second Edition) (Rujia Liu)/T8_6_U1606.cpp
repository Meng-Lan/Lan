#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 1005;

struct Point{
	int x, y;
	double res;
	bool operator< (const Point &t) {
		return res < t.res;
	}
}in[maxn],t[maxn];
int n,r[maxn];

bool Left(const Point &A, const Point &B) {
	return A.x*B.y - A.y*B.x >= 0;
}

int solve() {
	if (n <= 2) return 2;
	int ans = 0;
	FOR(i, n) {
		int k = 0;
		FOR(j, n) if (i != j) {
			t[k].x = in[j].x - in[i].x;
			t[k].y = in[j].y - in[i].y;
			if (r[j]) {
				t[k].x = -t[k].x;
				t[k].y = -t[k].y;
			}
			t[k].res = atan2(t[k].y, t[k].x);
			++k;
		}
		sort(t, t + k);
		int L = 0, R = 0, cnt = 2;
		while (L < k) {
			if (L == R) {
				++cnt;
				R = (R + 1) % k;
			}
			while (L != R&&Left(t[L], t[R])) {
				++cnt;
				R = (R + 1) % k;
			}
			--cnt; ++L;
			ans = max(ans, cnt);
		}
	}
	return ans;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		FOR(i, n) scanf("%d%d%d", &in[i].x, &in[i].y, r + i);
		printf("%d\n", solve());
	}
	return 0;
}