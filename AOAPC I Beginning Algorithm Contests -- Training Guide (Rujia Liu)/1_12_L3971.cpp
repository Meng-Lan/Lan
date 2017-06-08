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

const int maxn = 1e3 + 10;
struct Lan {
	int cost, quality;
	Lan(int c, int q) :cost(c), quality(q) {}
};

std::map<std::string, int> kinds;
int cnt = 0;
int ID(const std::string &s) {
	if (kinds.find(s) != kinds.end()) return kinds[s];
	return kinds[s] = cnt++;
}

int n, money;
std::vector<Lan> comp[maxn];

bool check(int q) {
	int sum = 0;
	FOR(i, 0, cnt) {
		int min = money + 1, len = comp[i].size();
		FOR(j, 0, len)
			if (comp[i][j].quality >= q)
				min = std::min(min, comp[i][j].cost);
		sum += min;
		if (sum > money) return false;
	}
	return true;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &money);
		FOR(i, 0, n) comp[i].clear();
		kinds.clear(); cnt = 0;
		char kind[30], name[30];
		int c, q, maxq = 0;
		FOR(i, 0, n) {
			scanf(" %s %s%d%d", kind, name, &c, &q);
			int id = ID(std::string(kind));
			comp[id].push_back(Lan(c, q));
			maxq = std::max(maxq, q);
		}
		int L = 0, R = maxq;
		while (L < R) {
			int m = L + (R - L + 1) / 2;
			if (check(m)) L = m;
			else R = m - 1;
		}
		printf("%d\n", L);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}