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

const int maxn = 5e5 + 10;
struct Lan {
	P sub;
	int perfix, suffix;
	Lan(P sub, int perfix, int suffix) :sub(sub), perfix(perfix), suffix(suffix) {}
	Lan() :Lan(P(0,0), 0, 0) {}
}tree[maxn << 2];
int in[maxn], n, q, ql, qr, kase;
ll sum[maxn];

void build(int rt, int l, int r) {
	if (l == r) {
		tree[rt] = Lan(P(l, r), l, r);
		return;
	}
	int m = l + (r - l) / 2;
	build(rt << 1, l, m);
	build(rt << 1 | 1, m + 1, r);
	ll sum1 = sum[tree[rt << 1].sub.second] - sum[tree[rt << 1].sub.first - 1], sum2 = sum[tree[rt << 1 | 1].sub.second] - sum[tree[rt << 1 | 1].sub.first - 1];
	if (sum1 >= sum2) tree[rt].sub = tree[rt << 1].sub;
	else tree[rt].sub = tree[rt << 1 | 1].sub;
	sum1 = std::max(sum1, sum2);
	if (sum[tree[rt << 1 | 1].perfix] - sum[tree[rt << 1].perfix] > 0) tree[rt].perfix = tree[rt << 1 | 1].perfix;
	else tree[rt].perfix = tree[rt << 1].perfix;
	if (sum[tree[rt << 1 | 1].suffix - 1] - sum[tree[rt << 1].suffix - 1] >= 0) tree[rt].suffix = tree[rt << 1].suffix;
	else tree[rt].suffix = tree[rt << 1 | 1].suffix;
	sum2 = sum[tree[rt << 1 | 1].perfix] - sum[tree[rt << 1].suffix - 1];
	if (sum2 > sum1 || sum2 == sum1&&tree[rt << 1].suffix < tree[rt].sub.first ||
		sum2 == sum1&&tree[rt << 1].suffix == tree[rt].sub.first&&tree[rt << 1 | 1].perfix < tree[rt].sub.second) tree[rt].sub = P(tree[rt << 1].suffix, tree[rt << 1 | 1].perfix);
}

Lan query(int rt, int l, int r) {
	if (ql <= l&&r <= qr) return tree[rt];
	int m = l + (r - l) / 2;
	Lan t1, t2;
	if (ql <= m) t1 = query(rt << 1, l, m);
	if (qr > m) t2 = query(rt << 1 | 1, m + 1, r);
	if (ql <= m&&qr > m) {
		Lan ans;
		ll sum1 = sum[t1.sub.second] - sum[t1.sub.first - 1], sum2 = sum[t2.sub.second] - sum[t2.sub.first - 1];
		if (sum1 >= sum2) ans.sub = t1.sub; else ans.sub = t2.sub;
		sum1 = std::max(sum1, sum2); sum2 = sum[t2.perfix] - sum[t1.suffix - 1];
		if (sum2 > sum1 || sum2 == sum1&&t1.suffix < ans.sub.first ||
			sum2 == sum1&&t1.suffix == ans.sub.first&&t2.perfix < ans.sub.second) ans.sub = P(t1.suffix, t2.perfix);
		if (sum[t2.perfix] - sum[t1.perfix] > 0 && t2.perfix <= qr) ans.perfix = t2.perfix; else ans.perfix = t1.perfix;
		if (sum[t2.suffix - 1] - sum[t1.suffix - 1] >= 0 && t1.suffix >= ql)ans.suffix = t1.suffix; else ans.suffix = t2.suffix;
		return ans;
	}
	if (ql <= m) return t1;
	if (qr > m) return t2;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d", &n, &q) == 2 && n) {
		For(i, 1, n) scanf("%d", in + i);
		sum[0] = 0;
		For(i, 1, n) sum[i] = sum[i - 1] + in[i];
		build(1, 1, n);
		printf("Case %d:\n", ++kase);
		FOR(i, 0, q) {
			scanf("%d%d", &ql, &qr);
			Lan ans = query(1, 1, n);
			printf("%d %d\n",ans.sub.first,ans.sub.second);
		}
	}

#ifdef MengLan
	//printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}