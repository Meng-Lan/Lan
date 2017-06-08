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
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 5010;
int in[maxn], n, T;
std::map<P, int> Min, Max;


int min(int l, int r) {
	if (Min.find({ l,r }) != Min.end()) return Min[{l, r}];
	if (l + 1 >= r) return Min[{l, r}] = in[l];
	int m = l + (r - l) / 2;
	return Min[{l, r}] = std::min(min(l, m), min(m, r));
}

int max(int l, int r) {
	if (Max.find({ l,r }) != Max.end()) return Max[{l, r}];
	if (l + 1 >= r) return Max[{l, r}] = in[l];
	int m = l + (r - l) / 2;
	return Max[{l, r}] = std::max(max(l, m), max(m, r));
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		FOR(i, 0, n) scanf("%d", in + i);
		min(0, n); max(0, n);
		for (auto &t : Max) printf("L:%d R:%d max:%d\n", t.first.first, t.first.second, t.second);
		for (auto &t : Min) printf("L:%d R:%d min:%d\n", t.first.first, t.first.second, t.second);
		bool ok = false;
		FOR(q, 1, n - 2) if (!ok)FOR(s, q + 2, n) {
			printf("Min  P:%d q:%d R:%d s%d\n", Min[{0, q}], q, Min[{q + 1, s}], s);
			printf("Max  P:%d q:%d R:%d s%d\n", Max[{0, q}], q, Max[{q + 1, s}], s);
			if (ok) break;
		}
		if (ok) printf("YES\n");
		else printf("NO\n");
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}