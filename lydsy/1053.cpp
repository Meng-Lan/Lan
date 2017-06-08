#include<iostream>
#include<cstdio>
#include<string.h>

using std::cin;
using std::endl;
using std::cout;
typedef unsigned long long ULL;
const ULL INF = ~0ULL;

ULL n, ans;
int p[16] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53 };
int best;
void dfs(int dept, ULL temp, int num) {
	if (dept >= 16)
		return;
	if (num > best) {
		best = num;
		ans = temp;
	}
	if (num == best&&ans > temp)
		ans = temp;
	for (int i = 1; i < 64; i++) {
		if (n / p[dept] < temp)
			break;
		dfs(dept + 1, temp *= p[dept], num*(i + 1));
	}
}
int main() {
	cin >> n;
	ans = INF;
	dfs(0, 1, 1);
	cout << ans << endl;
	return 0;
}