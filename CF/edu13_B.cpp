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

int main() {
	int y;
	cin >> y;
	bool sta = false;
	if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) sta = true;
	int day = 0;
	for (int i = 1;; ++i) {
		int t = y + i;
		bool lp = false;
		if (t % 4 == 0 && t % 100 != 0 || t % 400 == 0) {
			day += 2; lp = true;
		}
		else ++day;
		if (day % 7 == 0 && sta == lp) {
			printf("%d\n", t);
			break;
		}
	}
	return 0;
}