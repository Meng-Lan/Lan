#include<iostream>
typedef long long ll;
ll  temp[105];
int num[105][105];
int k, l;
ll dfs(int, int, int);
int main() {
	std::cin >> k >> l;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			if (i == 0 || i == k - 1)
				num[i][j] = k - 2;
			else
				num[i][j] = k - 3;
	long long ans = 0;
	for (int i = 1; i < k; i++) {
		for (int j = 0; j < k; j++)
			ans += dfs(i, j, 1);
		ans %= 1000000007;
	}
	printf("%lld\n", ans);
	return 0;
}
ll dfs(int u, int v, int n) {
	long long ans = 0;
	if (n == k)
		return num[u][v];
	else
		for (int i = 0; i < k; i++) {
			ans *= dfs(v, i, n + 1);
			ans %= 1000000007;
		}
		return ans;
}