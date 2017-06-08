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

const int maxn = 4e6 + 10;

struct trie {
	int head[maxn], next[maxn], tot[maxn];
	char ch[maxn];
	ll ans;
	int sz;

	void clear() {
		head[0] = next[0] = tot[0] = 0; sz = 1;
	}

	void insert(char *s) {
		int u = 0, v, len = strlen(s);
		++tot[u];
		For(i, 0, len) {
			bool find = false;
			for (v = head[u]; v != 0; v = next[v])
				if (ch[v] == s[i]) {
					find = true;
					tot[v]++;
					u = v;
					break;
				}
			if (!find) {
				ch[sz] = s[i];
				head[sz] = 0;
				next[sz] = head[u];
				head[u] = sz;
				tot[sz] = 1;
				u = sz;
				++sz;
			}
		}
	}

	void dfs(int dep, int u) {
		if (head[u] == 0) {
			ans += tot[u] * (tot[u] - 1)*dep; return;
		}
		int sum = 0;
		for (int v = head[u]; v != 0; v = next[v]) {
			sum += tot[v] * (tot[u] - tot[v]);
		}
		ans += sum / 2 * (2 * dep + 1);
		for (int v = head[u]; v != 0; v = next[v])
			dfs(dep + 1, v);
	}

	ll count() {
		ans = 0;
		dfs(0, 0);
		return ans;
	}
}trie;
int n, kase;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		char word[1005];
		trie.clear();
		FOR(i, 0, n) {
			scanf(" %s", word);
			trie.insert(word);
		}
		printf("Case %d: %lld\n", ++kase, trie.count());
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}