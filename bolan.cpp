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

struct tree {
	char c;
	tree *l, *r;
	tree(char c, tree *L, tree *R) :c(c), l(L), r(R) {}
	tree(char c) :c(c) {
		l = r = NULL;
	}
	tree() {
		c = ' ';
		l = r = NULL;
	}
};

std::stack<tree*> S;

const int maxn = 105;
char s[maxn];

void PostOrderTraverse(tree *R) {
	if (R->l != NULL) PostOrderTraverse(R->l);
	if (R->r != NULL) PostOrderTraverse(R->r);
	putchar(R->c);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%s", s);
	int len = strlen(s);
	for (int i = len - 1; i >= 0; --i) {
		if (isalpha(s[i])) {
			tree *node = new tree(s[i]);
			S.push(node);
		}
		else {
			tree *n1 = S.top(); S.pop();
			tree *n2 = S.top(); S.pop();
			tree *node = new tree(s[i], n1, n2);
			S.push(node);
		}
	}
	if (!S.empty()) {
		tree *T = S.top(); S.pop();
		PostOrderTraverse(T);
		putchar('\n');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}