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

const int maxn = 1e4 + 10;
struct Ants {
	int x, dir;
	int no;
	//Ants(int x, int d) :x(x), dir(d) {}
	void run(int T) {
		x += dir*T;
	}
	bool operator<(const Ants &rhs) const {
		return x < rhs.x;
	}
}in[maxn]; 
int no[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	For(kase, 1, T) {
		int l, t, n;
		scanf("%d%d%d", &l, &t, &n);
		int x;
		char s[10];
		FOR(i, 0, n) {
			scanf("%d %s", &x, s);
			in[i].x = x;
			if (s[0] == 'L') in[i].dir = -1;
			else in[i].dir = 1;
			in[i].no = i;
		}
		std::sort(in, in + n);
		FOR(i, 0, n) {
			no[in[i].no] = i;
			in[i].run(t);
		}
		std::sort(in, in + n);
		FOR(i, 1, n) if (in[i].x == in[i - 1].x) in[i].dir = in[i - 1].dir = 0;
		printf("Case #%d:\n", kase);
		FOR(i, 0, n) {
			Ants &tmp = in[no[i]];
			if (tmp.x<0 || tmp.x>l) puts("Fell off");
			else {
				printf("%d ", tmp.x);
				if (tmp.dir == -1) puts("L");
				else if (tmp.dir == 0) puts("Turning");
				else puts("R");
			}
		}
		puts("");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}