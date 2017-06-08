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

const int INF = 1e9;
const int maxn = 1e6 + 10;
struct Lan {
	int minv, maxv, sumv, addv, setv;
	Lan(int min, int max, int sum, int add, int set) :minv(min), maxv(max), sumv(sum), addv(add), setv(set) {}
	Lan(int min, int max, int sum) :Lan(min, max, sum, 0, -1) {}
	Lan() :Lan(0, 0, 0, 0, -1) {}
}tree[maxn << 2], *p[25];
int r, c, m;

void build(Lan *tr, int o, int l, int r) {
	tr[o] = Lan();
	if (l == r) return;
	int m = l + (r - l) / 2;
	build(tr, o << 1, l, m);
	build(tr, o << 1 | 1, m + 1, r);
}

int v, L, R;

void pushdowm(Lan *tr, int o) {
	int lc = o << 1, rc = o << 1 | 1;
	if (tr[o].setv >= 0) {
		tr[lc].setv = tr[rc].setv = tr[o].setv;
		tr[lc].addv = tr[rc].addv = tr[o].addv;
		tr[o].setv = -1; tr[o].addv = 0;
	}
	else {
		tr[lc].addv += tr[o].addv; tr[rc].addv += tr[o].addv;
		tr[o].addv = 0;
	}
}

void maintain(Lan *tr, int o, int l, int r) {
	int lc = o << 1, rc = o << 1 | 1;
	tr[o].sumv = tr[o].minv = tr[o].maxv = 0;
	if (tr[o].setv >= 0) {
		tr[o].minv = tr[o].maxv = tr[o].setv;
		tr[o].sumv = (r - l + 1)*tr[o].setv;
	}
	else if (l < r) {
		tr[o].sumv = tr[lc].sumv + tr[rc].sumv;
		tr[o].minv = std::min(tr[lc].minv, tr[rc].minv);
		tr[o].maxv = std::max(tr[lc].maxv, tr[rc].maxv);
	}
	tr[o].sumv += (r - l + 1)*tr[o].addv; tr[o].maxv += tr[o].addv; tr[o].minv += tr[o].addv;
}

void update(Lan *tr, int o, int l, int r, int op) {
	int lc = o << 1, rc = o << 1 | 1;
	if (L <= l&&r <= R) {
		if (!op) tr[o].addv += v;
		else {
			tr[o].addv = 0;
			tr[o].setv = v;
		}
	}
	else {
		pushdowm(tr, o);
		int m = l + (r - l) / 2;
		if (L <= m) update(tr, lc, l, m, op); else maintain(tr, lc, l, m);
		if (R > m) update(tr, rc, m + 1, r, op); else maintain(tr, rc, m + 1, r);
	}
	maintain(tr, o, l, r);
	//printf("l:%d r:%d sum:%d min:%d max:%d setv:%d addv:%d\n", l, r, tr[o].sumv, tr[o].minv, tr[o].maxv, tr[o].setv, tr[o].addv);
}

void add(int x1, int x2) {
	For(i, x1, x2) {
		update(p[i], 1, 1, c, 0);
	}
}

void set(int x1, int x2) {
	For(i, x1, x2) {
		update(p[i], 1, 1, c, 1);
	}
}

int min, max, sum;

void query(Lan *tr, int o, int l, int r,int add) {
	if (tr[o].setv >= 0) {
		sum += (std::min(r, R) - std::max(l, L) + 1)*(tr[o].setv + tr[o].addv + add);
		min = std::min(min, tr[o].minv + add);
		max = std::max(max, tr[o].maxv + add);
	}
	else if (L <= l&&r <= R) {
		sum += tr[o].sumv + (r - l + 1)*add;
		min = std::min(min, tr[o].minv + add);
		max = std::max(max, tr[o].maxv + add);
	}
	else {
		int m = l + (r - l) / 2;
		if (L <= m) query(tr, o << 1, l, m, add + tr[o].addv);
		if (R > m) query(tr, o << 1 | 1, m + 1, r, add + tr[o].addv);
	}
	//printf("l:%d r:%d sum:%d min:%d max:%d setv:%d addv:%d\n", l, r, tr[o].sumv, tr[o].minv, tr[o].maxv, tr[o].setv, tr[o].addv);
}

void query(int x1, int x2) {
	min = INF, max = -INF, sum = 0;
	For(i, x1, x2) {
		//printf("Q #%d\n", i);
		query(p[i], 1, 1, c, 0);
		//printf("#%d sum:%d min:%d max:%d\n", i, sum, min, max);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d%d", &r, &c, &m) == 3) {
		For(i, 1, r) p[i] = &tree[(i - 1)*(c << 2)];
		For(i, 1, r) build(p[i], 1, 1, c);
		int op, x1, x2;
		FOR(i, 0, m) {
			scanf("%d%d%d%d%d", &op, &x1, &L, &x2, &R);
			if (op == 1) {
				scanf("%d", &v); add(x1, x2);
			}
			if (op == 2) {
				scanf("%d", &v); set(x1, x2);
			}
			if (op == 3) {
				query(x1, x2);
				printf("%d %d %d\n", sum, min, max);
			}
		}
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}