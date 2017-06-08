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

char s[10][5][4] = {
{ " - ","| |","   ","| |"," - " },{ "   ","  |","   ","  |","   " },
{ " - ","  |"," - ","|  "," - " },{ " - ","  |"," - ","  |"," - " },
{ "   ","| |"," - ","  |","   " },{ " - ","|  "," - ","  |"," - " },
{ " - ","|  "," - ","| |"," - " },{ " - ","  |","   ","  |","   " },
{ " - ","| |"," - ","| |"," - " },{ " - ","| |"," - ","  |"," - " } };
char t[1<<8];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int k; scanf("%d", &k);
	scanf(" %s", t);
	int len = strlen(t);
	FOR(i, 0, len) t[i] -= '0';
	FOR(i, 0, len) { if (i)putchar(' '); putchar(s[t[i]][0][0]); FOR(l, 0, k)putchar(s[t[i]][0][1]); putchar(s[t[i]][0][2]); }putchar('\n');
	FOR(j, 0, k) { FOR(i, 0, len) { if (i)putchar(' '); putchar(s[t[i]][1][0]); FOR(l, 0, k)putchar(s[t[i]][1][1]); putchar(s[t[i]][1][2]); }putchar('\n'); }
	FOR(i, 0, len) { if (i)putchar(' '); putchar(s[t[i]][2][0]); FOR(l, 0, k)putchar(s[t[i]][2][1]); putchar(s[t[i]][2][2]); }putchar('\n');
	FOR(j, 0, k) { FOR(i, 0, len) { if (i)putchar(' '); putchar(s[t[i]][3][0]); FOR(l, 0, k)putchar(s[t[i]][3][1]); putchar(s[t[i]][3][2]); }putchar('\n'); }
	FOR(i, 0, len) { if (i)putchar(' '); putchar(s[t[i]][4][0]); FOR(l, 0, k)putchar(s[t[i]][4][1]); putchar(s[t[i]][4][2]); }putchar('\n');




#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}