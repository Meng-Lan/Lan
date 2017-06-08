#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }
std::vector<int> Eratosthenes(const int len, int *vis) {
	memset(vis, 0, sizeof(int)*len);
	std::vector<int> prime;
	int m = (int)sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n, int *phi) {
	For(i, 2, n) phi[i] = 0;
	phi[1] = 1;
	For(i, 2, n) if (!phi[i])
		for (int j = i; j <= n; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i*(i - 1);
		}
}

const int maxn = 2e5 + 10;
P tree[maxn], p[25];
int fa[maxn], n, cnt, q, in[25];
std::vector<int> sons[maxn];

void build(int fa) {
	FOR(i, 0, sons[fa].size()) {
		int l = cnt;
		build(sons[fa][i]);
		int r = cnt++;
		tree[sons[fa][i]] = mp(l, r);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	For(i, 1, n) { scanf("%d", fa + i); sons[fa[i]].push_back(i); }
	//FOR(i, 0, n) for (auto &t : sons[i]) printf("n:%d sons:%d\n", i, t);
	build(0);
	//For(i, 0, n) printf("#%d L:%d R:%d\n", i, tree[i].first, tree[i].second);
	scanf("%d", &q);
	while (q--) {
		int m; scanf("%d", &m);
		FOR(j, 0, m) scanf("%d", in + j);
		FOR(j, 0, m) {
			//printf("J:%d\n", in[j]);
			p[j].first = tree[in[j]].first;
			p[j].second = tree[in[j]].second;
			//printf("P L:%d R:%d\n", p[j].first, p[j].second);
		}
		std::sort(p, p + m);
		int r = 0;
		int ans = 0;
		FOR(i, 0, m) {
			//printf("L%d R:%d r:%d ans:%d\n", p[i].first, p[i].second, r,ans);
			if (!i) {
				ans += p[i].second - p[i].first + 1;
				r = p[i].second + 1; continue;
			}
			if (r > p[i].first) {
				if (p[i].second < r) continue;
				ans += p[i].second - r + 1;
				r = p[i].second + 1;
			}
			else {
				ans += p[i].second - p[i].first + 1;
				r = p[i].second + 1;
			}
		}

		printf("%d\n", ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}