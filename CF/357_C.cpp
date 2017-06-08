#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
#include<functional>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair
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

const int maxn = 1000000 + 10;
char ans[maxn][22];

int main() {
	int n;
	scanf("%d", &n);
	priority_queue<int,vector<int>,greater<int> > q;
	char s[15];
	int tmp = 1, kase = 0;
	/*q.push(1); q.push(2); q.push(-10);
	while (!q.empty()) {
		cout << q.top() << endl;
		q.pop();
	}*/
	while (n--) {
		scanf(" %s", s);
		if (strcmp(s, "insert") == 0) {
			scanf("%d", &tmp);
			q.push(tmp);
			sprintf(ans[kase], "insert %d\n", tmp); ++kase;
		}
		else if (strcmp(s, "removeMin") == 0) {
			if (q.empty()) {
				sprintf(ans[kase], "insert %d\n", tmp); ++kase;
				q.push(tmp);
			}
			q.pop();
			sprintf(ans[kase], "removeMin\n"); ++kase;
		}
		else if (strcmp(s, "getMin") == 0) {
			scanf("%d", &tmp);
			for (;;) {
				if (q.empty()) {
					sprintf(ans[kase], "insert %d\n", tmp); ++kase;
					q.push(tmp);
					sprintf(ans[kase], "getMin %d\n", tmp); ++kase;
					break;
				}
				else if (!q.empty() && q.top() == tmp) {
					sprintf(ans[kase], "getMin %d\n", tmp); ++kase;
					break;
				}
				else if (!q.empty() && q.top() > tmp) {
					sprintf(ans[kase], "insert %d\n", tmp); ++kase;
					q.push(tmp);
					sprintf(ans[kase], "getMin %d\n", tmp); ++kase;
					break;
				}
				else if (!q.empty() && q.top() < tmp) {
					sprintf(ans[kase], "removeMin\n"); ++kase;
					q.pop();
				}
			}
		}
	}
	printf("%d\n", kase);
	for (int i = 0; i < kase; ++i)
		printf("%s", ans[i]);
	return 0;
}