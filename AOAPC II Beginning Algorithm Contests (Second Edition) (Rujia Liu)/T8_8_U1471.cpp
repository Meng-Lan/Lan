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

struct Lan {
	int a, g;
	Lan(int a, int g) :a(a), g(g) {}
	bool operator<(const Lan &t) const {
		return a < t.a;
	}
};

set<Lan> s;
const int maxn = 1e5 * 2 + 10;
int in[maxn],n,f[maxn],g[maxn];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		FOR(i, n) scanf("%d", in + i);
		if (n == 1) {
			printf("1\n"); continue;
		}
		g[0] = 1;
		rep(i, 1, n)if (in[i]>in[i - 1]) g[i] = g[i - 1] + 1;
		else g[i] = 1;
		f[n - 1] = 1;
		for (int i = n - 2; i >= 0; --i)
			if (in[i] < in[i + 1]) f[i] = f[i + 1] + 1;
			else
				f[i] = 1;
		s.clear();
		s.insert(Lan(in[0], g[0]));
		int ans = 1;
		rep(i, 1, n) {
			Lan t(in[i], g[i]);
			auto it = s.lower_bound(t);
			bool keep = true;
			if (it != s.begin()) {
				Lan lase = *(--it);
				int len = f[i] + lase.g;
				ans = max(ans, len);
				if (t.g <= lase.g) keep = false;
			}
			if (keep) {
				s.erase(t);
				s.insert(t);
				it = s.find(t);
				++it;
				while (it != s.end() && it->a > t.a&&it->g <= t.g) s.erase(it++);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}