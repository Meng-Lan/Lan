#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
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
int maxd, n,ans[20];
const int maxans = 13;

bool check(const int &d) {
	for (int i = 0; i < d; i++)
		if (ans[i] == ans[d])
			return false;
	return true;
}

bool dfs(int d, int m) {
	if (d == maxd) {
		if (ans[d] == n) return true;
		return false;
	}
	if (m << (maxd - d) < n)
		return false;
	for (int j = d; j >= 0; j--) {
		ans[d + 1] = m + ans[j];
		if (check(d + 1) && dfs(d + 1, max(m, ans[d + 1]))) return true;
		ans[d + 1] = m - ans[j];
		if (check(d + 1) && dfs(d + 1, max(m, ans[d + 1]))) return true;
	}
	return false;
}

int solve(int n) {
	if (n == 1) return 0;
	ans[0] = 1;
	for (maxd = 1; maxd < maxans; maxd++)
		if (dfs(0, ans[0])) return maxd;
	return maxans;
}
int main() {
	while(scanf("%d",&n)==1&&n) {
		printf("%d\n", solve(n));
	}
	return 0;
}