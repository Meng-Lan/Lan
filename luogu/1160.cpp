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

const int maxn = 100010;
int L[maxn], R[maxn], n, m;

void insert(int k, int p, int i) {
	int l = L[k], r = R[k];
	if (p) {
		L[r] = i; R[i] = r;
		L[i] = k; R[k] = i;
	}
	else {
		R[l] = i; L[i] = l;
		R[i] = k; L[k] = i;
	}
}

void Delete(int x) {
	if (L[x] == 0 && R[x] == 0) return;
	int l = L[x], r = R[x];
	R[l] = r; L[r] = l;
	L[x] = R[x] = 0;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	int k, p;
	R[0] = 1;
	For(i, 2, n) {
		scanf("%d%d", &k, &p);
		insert(k, p, i);
	}
	scanf("%d", &m);
	FOR(i, 0, m) {
		int x; scanf("%d", &x);
		Delete(x);
	}
	int l = R[0], cnt = 0;
	while (l != 0) {
		if (cnt++) putchar(' ');
		printf("%d", l);
		l = R[l];
	}
	putchar('\n');

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}