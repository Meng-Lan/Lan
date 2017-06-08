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

const int maxn = 40010;
int in[maxn], n, t[maxn];

int sort(int l, int r) {
	if (l >= r) return 0;
	int ans = 0;
	int m = l + (r - l) / 2;
	if (r - l > 2) { ans = sort(l, m) + sort(m, r); }
	int p = l, q = m, cnt = l;
	while (p < m || q < r) {
		if (p < m&&q < r) {
			if (in[p] <= in[q]) t[cnt++] = in[p++];
			else { ans += m - p; t[cnt++] = in[q++]; }
		}
		else if (p < m) t[cnt++] = in[p++];
		else t[cnt++] = in[q++];
	}
	FOR(i, l, r) in[i] = t[i];
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock(); 
#endif // MengLan

	scanf("%d", &n);
	FOR(i, 0, n) scanf("%d", in + i);
	printf("%d\n", sort(0, n));



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}