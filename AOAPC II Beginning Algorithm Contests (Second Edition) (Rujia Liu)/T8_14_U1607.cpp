#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<functional>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair
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

const int maxn = 200000 + 10;
struct Gates {
	int a, b, o;
}gates[maxn];
int n, m;

int output(int v) {
	for (int i = 1; i <= m;++i) {
		int a = gates[i].a, b = gates[i].b;
		int va = a < 0 ? -a <= v : gates[a].o;
		int vb = b < 0 ? -b <= v : gates[b].o;
		gates[i].o = !(va&&vb);
	}
	return gates[m].o;
}

int solve(int v) {
	int L = 1, R = n;
	while (L < R) {
		int M = L + (R - L) / 2;
		if (output(M) == v) R = M;
		else L = M + 1;
	}
	return L;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i) scanf("%d%d", &gates[i].a, &gates[i].b);
		int v0 = output(0), vn = output(n);
		if (v0 == vn) FOR(i, n) putchar('0');
		else {
			int x = solve(vn);
			for (int i = 1; i < x; ++i) putchar('1');
			putchar('x');
			for (int i = x + 1; i <= n; ++i) putchar('0');
		}
		putchar('\n');
	}
	return 0;
}