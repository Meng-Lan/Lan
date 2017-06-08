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
typedef std::pair<ull, ull> P;
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
ull gcd(ull a, ull b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

/*  参考于http://blog.csdn.net/lighting_/article/details/50573433
，，，本来写的还有点区别的，结果一直WAWAWA，，，导致代码越改越像
，，，最后才找出问题关键，不是其他问题，是计算中间值溢出导致的WA*/

const int maxn = 100000 + 10;
struct Lan {
	ull nume, deno;
	Lan(const Lan &t) :Lan(t.nume, t.deno) {}
	Lan(ull x, ull y) :nume(x), deno(y) {}
	Lan(ull x) :Lan(x, 1) {}
	Lan() :Lan(0) {}
	Lan operator+(const Lan &t) {
		ull a = nume*t.deno + deno*t.nume, b = deno*t.deno;
		ull G = gcd(a, b);
		return Lan(a / G, b / G);
	}
	Lan operator+(const ull &t) { return Lan(nume + deno*t, deno); }
	Lan operator+=(const Lan &t) { *this = *this + t; return *this; }
	bool operator<(const Lan &t)const { return nume*t.deno < deno*t.nume; }
	bool operator<(const ull &t)const { return nume < t*deno; }
	bool operator<=(const ull &t)const { return nume <= t*deno; }
	bool operator>=(const ull &t)const { return nume >= t*deno; }
}now;
int n;
P in[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		Lan ans(1e7);
		//cout << ans.nume << '/' << ans.deno << endl;
		For(i, 1, n) {
			scanf("%d%d", &in[i].first, &in[i].second);
		}
		std::sort(in + 1, in + n + 1, [](const P &t1, const P &t2) {return t1.first < t2.first; });
		std::deque<ull> dq;
		For(i, 1, n) {
			if (dq.empty()) {
				dq.push_back(i);
				if (!(ans <= (in[i].second - in[i].first))) ans = Lan(in[i].second - in[i].first);
				now = ans + in[i].first;
				continue;
			}
			if (now <= in[i].first) { dq.clear(); --i; continue; }
			int R = dq.size();
			while (dq.size() > 1 && (i - dq[R - 1])*(in[dq[R - 1]].first - in[dq[R - 2]].first) <=
				(dq[R - 1] - dq[R - 2])*(in[i].first - in[dq[R - 1]].first)) {
				dq.pop_back(); R = dq.size();
			}
			dq.push_back(i);
			if (now + ans <= in[i].second) now = now + ans;
			else {
				while (dq.size() > 1 && (dq[1] - dq[0])*(in[i].second - in[dq[1]].first) <=
					(i - dq[1] + 1)*(in[dq[1]].first - in[dq[0]].first)) dq.pop_front();
				ull a = in[i].second - in[dq.front()].first, b = i - dq.front() + 1;
				ull G = gcd(a, b);
				ans = Lan(a / G, b / G);
				now = Lan(in[i].second);
			}
		}
		//FOR(i, 0, n) printf("#%d [%d,%d]\n", i + 1, in[i].first, in[i].second);
		cout << ans.nume << '/' << ans.deno << endl;
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}
/*
6
0 2
1 3
2 4
3 5
4 6
5 7
5
100 102
101 103
10 100
0 5
5 10
3
5 100
10 13
11 13
3
2 6
1 4
8 12
0

*/