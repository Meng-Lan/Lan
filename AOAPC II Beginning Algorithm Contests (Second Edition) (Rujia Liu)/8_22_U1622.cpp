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
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

ull n, m, N, S, E, W;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while((cin>>n>>m)&&n&&m){
		cin >> N >> S >> W >> E;
		ull ans = 0;
		{
			ull minwe = std::min(W, E);
			ull minns = std::min(N, S);
			ull ans1 = 0, ans2 = 0;
			if (minwe&&minns) {
				ans1 = n*m + n*(m - 1) * 2 * minwe + (n - 1)*(m - 1)*(2 * minns - 1);
				ans2 = n*m + (n - 1)*m * 2 * minns + (n - 1)*(m - 1)*(2 * minwe - 1);
				n -= 1; m -= 1;
			}
			else if (minwe) ans1 = ans2 = n*m + n*(m - 1)*(2 * minwe - 1), m -= 1;
			else if (minns) ans1 = ans2 = n*m + (n - 1)*m*(2 * minns - 1), n -= 1;
			ans = std::max(ans1, ans2);
			N -= minns; S -= minns; W -= minwe; E -= minwe;
		}
		{
			ull we = std::max(W, E);
			ull ns = std::max(N, S);
			if (m < we) we = m;
			if (n < ns) ns = n;
			ull ans1 = 0, ans2 = 0, ans3 = 0;
			if(we&&ns){
				ans1=n*(

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}