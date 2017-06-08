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
const int maxn = 1 << 6;
int n, isp[maxn],A[maxn],vis[maxn];
bool is_prime(int t) {
	int ok = true;
	for (int i = 2; i*i <= t; i++)
		if (t%i==0) {
			ok = false;
			break;
		}
	return ok;
}
void dfs(int cur) {
	if (cur == n&&isp[A[0] + A[n - 1]]) {
		printf("%d", A[0]);
		for (int i = 1; i < n; i++)
			printf(" %d", A[i]);
		putchar('\n');
	}
	else for (int i = 2; i <= n; i++)
		if (!vis[i] && isp[A[cur - 1] + i]) {
			A[cur] = i;
			vis[i] = 1;
			dfs(cur + 1);
			vis[i] = 0;
		}
}
int main() {
	int kase = 0;
	for (int i = 2; i < maxn; i++)
		isp[i] = is_prime(i);
	while (scanf("%d", &n) == 1) {
		if (kase)
			putchar('\n');
		memset(vis, 0, sizeof(vis));
		A[0] = 1;
		printf("Case %d:\n", ++kase);
		dfs(1);
	}
	return 0;
}