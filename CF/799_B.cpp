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
std::map<int, std::set<P>> front, back;
int n;
struct Lan {
	int p, a, b;
	Lan(int p, int a, int b) :p(p), a(a), b(b) {}
	Lan() :Lan(0, 0, 0) {}
}in[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	FOR(i, 0, n) scanf("%d", &in[i].p);
	FOR(i, 0, n) scanf("%d", &in[i].a);
	FOR(i, 0, n) scanf("%d", &in[i].b);
	FOR(i, 0, n) {
		//printf("P:%d a:%d b:%d\n", in[i].p, in[i].a, in[i].b);
		front[in[i].a].insert(P(in[i].p, i));
		back[in[i].b].insert(P(in[i].p, i));
	}
	int m,c; scanf("%d", &m);
	FOR(i, 0, m) {
		scanf("%d", &c);
		bool fe = front[c].empty(), be = back[c].empty();
		//printf("%d %d\n", fe, be);
		if (!fe && !be) {
			auto l = front[c].begin(), r = back[c].begin();
			if (l->first < r->first) {
				printf("%d%c", l->first, i != m - 1 ? ' ' : '\n');
				int idx = l->second;
				front[c].erase(l); back[in[idx].b].erase(P(in[idx].p, idx));
			}
			else {
				printf("%d%c", r->first, i != m - 1 ? ' ' : '\n');
				int idx = r->second;
				back[c].erase(r); front[in[idx].a].erase(P(in[idx].p, idx));
			}
		}
		if (!fe&&be) {
			auto l = front[c].begin();
			printf("%d%c", l->first, i != m - 1 ? ' ' : '\n');
			int idx = l->second;
			front[c].erase(l); back[in[idx].b].erase(P(in[idx].p, idx));
		}
		if (fe && !be) {
			auto r = back[c].begin();
			printf("%d%c", r->first, i != m - 1 ? ' ' : '\n');
			int idx = r->second;
			back[c].erase(r); front[in[idx].a].erase(P(in[idx].p, idx));
		}
		if (fe&&be) {
			printf("-1%c", i != m - 1 ? ' ' : '\n');
		}
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}