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

const int maxn = 305;
const ll Mod = 1000000007;
ll in;
int n, vis[2005],prime[2005];
std::map<std::set<int>, int> m;
std::set<std::set<int>> s;

int get_prime() {
	const int len = 2000;
	for (int i = 2; i <= len; ++i)
		for (int j = i * 2; j <= len; j += i) vis[j] = 1;
	int cnt = 0;
	For(i, 2, len) if (!vis[i]) prime[cnt++] = i;
	//FOR(i, 0, cnt) printf("%d ", prime[i]); putchar('\n');
	return cnt;
}

std::set<int> deco(ll x,const int &len) {
	std::set<int> si;
	for (int i = 0; i < len&&x; ++i) if (x%prime[i] == 0) {
		const int &p = prime[i];
		int cnt = 0;
		while (x%p == 0) { x /= p; ++cnt; }
		if (cnt % 2)
			si.insert(prime[i]);
	}
	return si;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int len = get_prime();
	int T; scanf("%d", &T);
	For(kase, 1, T) {
		scanf("%d", &n);
		m.clear();
		FOR(i, 0, n) {
			scanf("%I64d", &in);
			std::set<int> si = deco(in, len);
			std::vector <std::set<int>> vs;
			std::map<std::set<int>, int> tm=m;
			vs.emplace_back(si);
			++tm[si];
			for (auto &t : s) {
				auto tsi = si;
				for (auto &st : t) if (tsi.find(st) != tsi.end()) tsi.erase(st);
				else tsi.insert(st);
				tm[tsi] += m[t]; vs.emplace_back(tsi);
			}
			m = tm;
			for (auto &t : vs) s.insert(t);/* printf("size:%d\n", m.size());
			for (auto &t : m) {
				printf("%d #val: %d map:",i, t.second);
				for (auto &st : t.first) printf(" %d", st); putchar('\n');
			}*/
		}
		std::set<int> ans = deco(0, len);
		printf("Case #%d:\n%d\n",kase, m[ans]);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}