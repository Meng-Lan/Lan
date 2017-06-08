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

const int maxn = 30000000;
int cnt[maxn + 1], sum[maxn + 1];

void init() {
	For(c, 1, maxn) for (int a = c * 2; a <= maxn; a += c) {
		int b = a - c;
		if (c == (a^b)) ++cnt[a];
	}
	sum[0] = 0;
	For(i, 1, maxn) sum[i] = sum[i - 1] + cnt[i];
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	init();
	int T; scanf("%d", &T); 
	For(kase, 1, T) {
		int n; scanf("%d", &n);
		printf("Case %d: %d\n", kase, sum[n]);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}