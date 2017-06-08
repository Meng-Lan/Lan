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

const int maxn = 310;
int in[maxn], len;

bool equal(const std::deque<int> &dq) {
	FOR(i, 0, len) if (dq[i] != i + 1) return false;
	return true;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &len) == 1 && len) {
		FOR(i, 0, len) scanf("%d", in + i);
		std::deque<int> dq(in, in + len);
		std::string ans;
		for (;;) {
			if (equal(dq)) break;
			if (dq[0] > dq[1] && !(dq[0] == len&&dq[1]==1)) {
				std::swap(dq[0], dq[1]);
				ans += "1";
			}
			else {
				int t = dq.back(); dq.pop_back();
				dq.push_front(t); ans += "2";
			}
		}
		std::ostream_iterator<char> out(cout);
		std::copy(ans.rbegin(), ans.rend(), out);
		putchar('\n');
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}