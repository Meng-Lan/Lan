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
int c, n, total_dist[maxn], dist2origin[maxn], total_weight[maxn];
int x[maxn], y[maxn], q[maxn], d[maxn];

int func(int i) {
	return d[i] - total_dist[i + 1] + dist2origin[i + 1];
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &c, &n);
		total_dist[0] = total_weight[0] = x[0] = y[0] = 0;
		For(i, 1, n) {
			int w;
			scanf("%d%d%d", x + i, y + i, &w);
			dist2origin[i] = std::abs(x[i]) + std::abs(y[i]);
			total_weight[i] = total_weight[i - 1] + w;
			total_dist[i] = total_dist[i - 1] + std::abs(x[i] - x[i - 1]) + std::abs(y[i] - y[i - 1]);
		}
		int front, rear;
		front = rear = 1;
		For(i, 1, n) {
			while (front <= rear&&total_weight[i] - total_weight[q[front]] > c) front++;
			d[i] = func(q[front]) + total_dist[i] + dist2origin[i];
			while (front <= rear&&func(i) <= func(q[rear])) rear--;
			q[++rear] = i;
		}
		printf("%d\n", d[n]);
		if (T) printf("\n");
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}