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

const int maxn = 2e5 + 10;
int n, a, b, k;
char s[maxn];
struct Node {
	int l, r, len, num;
	Node(int l, int r) :l(l), r(r) {}
	Node() :Node(0, 0) {}
	void C() {
		len = r - l;
		num = len / b;
	}
	bool operator<(const Node &rhs)const {
		return len < rhs.len;
	}
};

std::vector<Node> d;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d%d %s", &n, &a, &b, &k, s);
	int l = 0;
	FOR(i, 0, n) {
		if (s[i] == '1') {
			l = i + 1; continue;
		}
		while (i < n&&s[i] == '0') ++i;
		d.push_back(Node(l, i));
		l = i + 1;
	}
	int num = 0;
	for (auto &t : d) { t.C(); num += t.num; }
	std::sort(d.begin(), d.end());
	int ans = num - a + 1;
	cout << ans << '\n';
	for (auto &t : d) {
		//printf("%d %d %d %d\n", t.l, t.r, t.num, t.len);
		int m = std::min(ans, t.num);
		ans -= m;
		FOR(i, 0, m) {
			printf("%d", t.l + (i+1)*b);
			if (ans || i != m - 1) putchar(' ');
			else putchar('\n');
		}
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}