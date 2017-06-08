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

const int maxn = 777;
const int INF = 1e9;
int A[2][maxn], n;

struct Lan {
	int s, b;
	Lan(int s, int b) :s(s), b(b) {}
	Lan() :Lan(0, 0) {}
	bool operator<(const Lan &rhs)const {
		return s > rhs.s;
	}
};

void merge(int *A, int *B, int *C, int n) {
	std::priority_queue<Lan> q;
	FOR(i, 0, n) q.push(Lan(A[i] + B[0], 0));
	FOR(i, 0, n) {
		Lan t = q.top(); q.pop();
		C[i] = t.s;
		t.s += B[t.b + 1] - B[t.b];
		++t.b;
		if (t.b < n) q.push(t);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		FOR(i, 0, n) scanf("%d", A[0] + i);
		FOR(i, 1, n) {
			FOR(j, 0, n) scanf("%d", A[1] + j);
			std::sort(A[1], A[1] + n);
			merge(A[0], A[1], A[0], n);
		}
		FOR(i, 0, n) printf("%d%c", A[0][i], i != n - 1 ? ' ' : '\n');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}