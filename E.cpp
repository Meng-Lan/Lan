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

ll ans;
char op[10];
int h, m, s, home, guest, b, kase;
const int cost[] = { 6,2,5,5,4,5,6,3,7,6 };

int trans() {
	return h * 3600 + m * 60 + s;
}

ll Cal(int sco,int len) {
	if (sco == 0) return (ll)len * 6;
	ll add = 0;
	while (sco) {
		int t = sco % 10; sco /= 10; add += cost[t] * len;
	}
	return add;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%s%d:%d:%d", op, &h, &m, &s) == 4) {
		ans = home = guest = 0;
		b = trans();
		while (scanf("%s%d:%d:%d", op, &h, &m, &s) == 4) {
			if (!strcmp(op, "SCORE")) {
				int add;
				scanf("%s%d", op, &add);
				int e = trans();
				ans += Cal(home, e - b) + Cal(guest, e - b);
				b = e;
				if (!strcmp(op, "home")) home += add;
				if (!strcmp(op, "guest")) guest += add;
			}
			if (!strcmp(op, "END")) {
				int e = trans();
				ans += Cal(home, e - b) + Cal(guest, e - b);
				break;
			}
		}
		printf("Case %d: %lld\n", ++kase, ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}