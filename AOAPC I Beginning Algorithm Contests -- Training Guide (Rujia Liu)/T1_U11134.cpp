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

const int maxn = 5e3 + 10;
struct Lan {
	int l, r, id;
	Lan(int l, int r, int id) :l(l), r(r), id(id) {}
	Lan() :Lan(0, 0, 0) {}
	bool operator<(const Lan &rhs)const { 
		return r > rhs.r;
	}
}x[maxn], y[maxn];
int ansx[maxn], ansy[maxn], n;

bool solve(Lan *tmp, int *ans) {
	std::priority_queue<Lan> q;
	int idx = 0;
	For(i, 1, n) {
		while (idx < n&&tmp[idx].l <= i) q.push(tmp[idx++]);
		if (q.empty()) return false;
		Lan top = q.top(); q.pop();
		if (top.r < i) return false;
		ans[top.id] = i;
	}
	return true;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		FOR(i, 0, n) {
			scanf("%d%d%d%d", &x[i].l, &y[i].l, &x[i].r, &y[i].r);
			x[i].id = y[i].id = i;
		}
		std::sort(x, x + n, [](const Lan &l, const Lan &r) {return l.l < r.l; });
		std::sort(y, y + n, [](const Lan &l, const Lan &r) {return l.l < r.l; });
		if (solve(x,ansx)&&solve(y,ansy)) FOR(i, 0, n) printf("%d %d\n", ansx[i], ansy[i]);
		else printf("IMPOSSIBLE\n");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}