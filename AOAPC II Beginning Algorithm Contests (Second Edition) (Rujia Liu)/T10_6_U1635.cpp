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
std::vector<int> prime;
void Eratosthenes() {
	const int len = 1;
	int vis[len]; memset(vis, 0, sizeof(vis));
	int m = sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
}

const int maxn = 1e5 + 10;
int bad[maxn];

void get_prime(int n) {
	int m = floor(sqrt(n) + 0.5);
	For(i, 2, m) if (n%i == 0) {
		prime.push_back(i);
		while (n%i == 0) { n /= i; }
	}
	if (n > 1) prime.push_back(n);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int n, m;
	while (scanf("%d%d", &n, &m)==2) {
		memset(bad, 0, sizeof(bad)); prime.clear();
		get_prime(m);
		--n;
		FOR(i, 0, prime.size()) {
			int e = 0, mine = 0;
			int x = m, p = prime[i];
			while (x%p == 0) { x /= p; ++mine; }
			FOR(k, 1, n) {
				x = n - k + 1;
				while (x%p == 0) {
					x /= p; ++e;
				}
				x = k;
				while (x%p == 0) {
					x /= p; --e;
				}
				if (e < mine) bad[k] = 1;
			}
		}
		std::vector<int> ans;
		FOR(i, 1, n) if (!bad[i]) ans.push_back(i + 1);
		cout << ans.size() << "\n";
		if (!ans.empty()) {
			cout << ans[0];
			for (int i = 1; i < ans.size(); i++) cout << " " << ans[i];
		}
		cout << "\n";
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}