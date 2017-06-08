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

//WA得不省人事，，，源自一个计数器i和j引发的血案。。。。。。。

const int maxn = 20000;
struct Lan {
	int grade[8];
}in[maxn];
int n, top[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		double grade[3];
		int Grade[3];
		For(i, 1, n) {
			scanf("%lf%lf%lf", &grade[0], &grade[1], &grade[2]);
			FOR(j, 0, 3) Grade[j] = (int)round((grade[j] * 100.0));
			for (int j = 0; j < 8; j++) {
				in[i].grade[j] = 0;
				for (int k = 0; k < 3; k++)
					if (j & (1 << k))
						in[i].grade[j] += Grade[k];
			}
			std::sort(in[i].grade, in[i].grade + 8);
		}
		For(i, 1, n) scanf("%d", &top[i]);

		P Max(in[top[1]].grade[7], top[1]);
		bool ok = true; int i;
		for (i = 2; i <= n; ++i) {
			ok = false;
			Lan &t = in[top[i]];
			for (int j = 7; j >= 0; --j) {
				if (t.grade[j] == Max.first&&top[i] > Max.second) {
					Max.second = top[i];
					ok = true; break;
				}
				if (t.grade[j] < Max.first) {
					Max = mp(t.grade[j], top[i]);
					ok = true; break;
				}
			}
			if (!ok) break;
		}
		printf("Case %d: ", ++kase);
		if (i != n + 1)
			printf("No solution\n");
		else
			printf("%.2f\n", Max.first / 100.0);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}