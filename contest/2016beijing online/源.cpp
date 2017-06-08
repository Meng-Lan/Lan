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

struct Node {
	std::string s;
	std::vector<Node*> v;
	int cnt = 0;

	Node(std::string s) :s(s) {}
	Node() :Node("") {}

	void Add_next(std::string s) {
		Node *t = new Node;
		t->s = s; t->cnt = 0;
		v.push_back(t);
	}
};

std::string s;

int add_tree(Node* root, int cnt, std::string s) {
	if (cnt >= s.size()) return 0;
	int n = s.find('/', cnt);
	//printf("b:%d e:%d ", cnt, n); cout << s.substr(cnt, n - cnt) << ' ';
	if (n == -1) n = s.size();
	int idx = -1;

	std::string t = s.substr(cnt, n - cnt);
	while (t.front() == ' ') t = t.substr(1);
	while (t.back() == ' ') t.pop_back();

	FOR(i, 0, root->v.size()) if (root->v[i]->s == t) {
		idx = i; break;
	}
	if (idx == -1) {
		root->Add_next(s.substr(cnt, n - cnt));
		idx = root->v.size() - 1;
	}
	//printf("idx:%d\n", idx);
	if (idx == -1) return false;
	return root->cnt = std::max(root->cnt, add_tree(root->v[idx], n + 1, s) + 1);
}

bool cmp2(Node *l, Node *r) {
	return l->cnt > r->cnt || l->cnt == r->cnt&&l->s < r->s;
}

bool cmp(Node *l, Node *r) {
	return l->s < r->s;
}

void print(Node *r, int cnt) {
	//cout << r->s; printf(" size:%d  cnt:%d\n", r->v.size(), r->cnt);
	FOR(i, 0, cnt - 1) printf("    ");
	if (cnt)cout << r->s << '\n';
	if (cnt) std::sort(r->v.begin(), r->v.end(), cmp2);
	else std::sort(r->v.begin(), r->v.end(), cmp);
	/*FOR(i, 0, r->v.size()) {
		if (i) putchar(' ');
		cout << r->v[i]->s;
	}putchar('\n');*/
	FOR(i, 0, r->v.size()) print(r->v[i], cnt + 1);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	

	int kase = 0;
	while (std::getline(cin, s)) {
		Node *tree = new Node;
		tree->s = ""; tree->v.clear(); tree->cnt = 0;
		do {
			if (s == "0") break;
			add_tree(tree, 0, s);
		} while (std::getline(cin, s));
		printf("Case %d:\n", ++kase);
		print(tree, 0);
	}



#ifdef MengLan
//	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}