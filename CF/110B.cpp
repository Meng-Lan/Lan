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

const int maxn = 1e5 + 10;
std::vector<int> yes[maxn], no[maxn];
int n, m, tmp, num, in[maxn];
char s[maxn];
bool vis[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &m);
	FOR(i, 0, n) {
		scanf(" %c%d", s + i, in + i);
		char &c = s[i];
		int &t = in[i];
		if (c == '+') {
			yes[t].push_back(i);
		}
		else {
			no[t].push_back(i); ++tmp;
		}
	}
	For(i, 0, n) if (yes[i].size() + tmp - no[i].size() == m) {
		vis[i] = true; ++num;
	}
	if (!num) {

	}
	if (m == 0) {
		FOR(i, 0, n) printf("Lie\n");
		return 0;
	}
	FOR(i, 0, n) {
		if (s[i] == '+') {
			if (vis[in[i]]) {
				if (num > 1) printf("Not defined\n");
				else printf("Truth\n");
			}
			else printf("Lie\n");
		}
		else {
			if (!vis[in[i]]) printf("Truth\n");
			else if (num == 1) printf("Lie\n");
			else printf("Not defined\n");
		}
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}
/*
4 3
-4
-3
-1
-3
*/