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

const int maxn = 6e4;
struct Node {
	int hash, left, right;
	std::string s;
	Node(int h) :hash(h), s(""), left(-1), right(-1) {}
	Node() :Node(0) {}
	bool operator<(const Node &rh)const {
		if (hash != rh.hash) return hash < rh.hash;
		if (left != rh.left) return left < rh.left;
		return right < rh.right;
	}
}node[maxn];
int vis[maxn], kase, cnt;
char str[maxn * 5], *p;
std::map<Node, int> dict;

int build() {
	int id = cnt++;
	Node &t = node[id];
	t = Node();
	while (isalpha(*p)) {
		t.hash = t.hash * 27 + (*p) - 'a' + 1;
		t.s.push_back(*p); ++p;
	}
	if (*p == '(') {
		++p; t.left = build(); ++p; t.right = build(); ++p;
	}
	if (dict.count(t) != 0) {
		--cnt; return dict[t];
	}
	return dict[t] = id;
}

void print(int fa) {
	if (vis[fa] == kase) {
		printf("%d", fa + 1);
	}
	else {
		vis[fa] = kase;
		Node &u = node[fa];
		cout << u.s;
		if (u.left != -1) {
			putchar('('); print(u.left);
			putchar(',');
			print(u.right); putchar(')');
		}
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		++kase;
		scanf("%s", str);
		cnt = 0; dict.clear();
		p = str;
		print(build());
		putchar('\n');
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}