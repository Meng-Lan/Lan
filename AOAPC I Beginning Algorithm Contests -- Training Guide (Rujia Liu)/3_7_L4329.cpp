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

const int maxn = 2e4 + 10;
const int maxr = 1e5 + 10;
int n, in[maxn], t[maxr], c[maxn], d[maxn];

inline int lowbit(int x) {
	return x&-x;
}

int sum(int x) {
	int ret = 0;
	while (x > 0) {
		ret += t[x]; x -= lowbit(x);
	}
	return ret;
}

void add(int x, int d) {
	while (x < maxr) {
		t[x] += d; x += lowbit(x);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(t, 0, sizeof(t));
		For(i, 1, n) {
			scanf("%d", in + i);
			add(in[i], 1);
			c[i] = sum(in[i] - 1);
		}
		memset(t, 0, sizeof(t));
		for (int i = n; i >= 1; --i) {
			add(in[i], 1);
			d[i] = sum(in[i] - 1);
		}
		//For(i, 1, n) printf("c#%d %d\n", i, c[i]);
		//For(i, 1, n) printf("d#%d %d\n", i, d[i]);
		ll ans = 0;
		For(i, 1, n) ans += (ll)c[i] * (n - i - d[i]) + (i - c[i] - 1)*d[i];
		printf("%lld\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}