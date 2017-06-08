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

const int maxn = 100010;
int in[maxn], n, L[maxn], R[maxn];
ll sum[maxn];
struct Lan {
	int val, idx;
	Lan(int val, int idx) :val(val), idx(idx) {}
	Lan() :Lan(0, 0) {}
	bool operator<(const Lan &t)const {
		return val < t.val;
	}
	bool operator>(const int &t) const {
		return val > t;
	}
};

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		if (kase) putchar('\n'); ++kase;
		For(i, 1, n) scanf("%d", in + i);
		std::priority_queue<Lan> q;
		For(i, 1, n) {
			while (!q.empty() && q.top() > in[i]) {
				R[q.top().idx] = i - 1; q.pop();
			}
			q.push(Lan(in[i], i));
		}
		while (!q.empty()) {
			R[q.top().idx] = n; q.pop();
		}
		for (int i = n; i >= 1; --i) {
			while (!q.empty() && q.top() > in[i]) {
				L[q.top().idx] = i + 1; q.pop();
			}
			q.push(Lan(in[i], i));
		}
		while (!q.empty()) {
			L[q.top().idx] = 1; q.pop();
		}
		For(i, 1, n) sum[i] = sum[i - 1] + in[i];
		ll Max = 0; P ans(1, 1);
		For(i, 1, n) if ((ll)(sum[R[i]] - sum[L[i] - 1])*in[i] > Max) {
			Max = (ll)(sum[R[i]] - sum[L[i] - 1])*in[i];
			ans.first = L[i]; ans.second = R[i];
		}
		//For(i, 1, n) printf("#%d L:%d R:%d\n", i, L[i], R[i]);
		printf("%lld\n%d %d\n", Max, ans.first, ans.second);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}