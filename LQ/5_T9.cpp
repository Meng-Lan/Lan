#include<iostream>
typedef long long ll;
ll ans = 0;
int num[55][55];
int m, n, k;
void dfs(int, int, int, int);
int main() {
	std::cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> num[i][j];
	dfs(0, 0, 0, 0);
	std::cout << ans << std::endl;
	return 0;
}
void dfs(int x, int y, int max, int cur) {
	if (cur == k) {
		if (ans > 1000000007)
			ans -= 1000000007;
		ans++;
		return;
	}
	else if (n - 1 == x&&m - 1 == y&&cur + 1 == k&&num[x][y]>max) {
		if (ans > 1000000007)
			ans -= 1000000007;
		ans++;
		return;
	}
	else {
		if (x + 1 < n) {
			if (num[x][y] > max)
				dfs(x + 1, y, num[x][y], cur + 1);
			dfs(x + 1, y, max, cur);
		}
		if (y + 1 < m) {
			if (num[x][y] > max)
				dfs(x, y + 1, num[x][y], cur + 1);
			dfs(x, y + 1, max, cur);
		}
	}
}