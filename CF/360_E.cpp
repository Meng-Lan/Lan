#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<list>
#include<forward_list>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<functional>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
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

const int maxn = 1000010;
int in[maxn],tmp[maxn];


int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	ll ans = 1;
	bool sta = false;
	queue<int> q;
	FOR(i, 0, n) {
		scanf("%d", in + i);
		tmp[in[i]] = 1;
		ans = lcm(ans, in[i]);
		if (!tmp[ans]) q.push(ans);
		if (ans%k == 0) sta = true;
	}
	while(!q.empty()){
		ans = lcm(ans, q.front());
		q.pop();
		
	if (ans%k == 0 || sta)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}