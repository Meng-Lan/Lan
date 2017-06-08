#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
const int maxn = 100005;
int ans[maxn];
int main() {
	for (int i = 0; i < maxn; i++) {
		int x = i, y = i;
		while (x > 0) {
			y += x % 10;
			x /= 10;
		}
		if (y >= maxn) continue;
		if (!ans[y] || i < ans[y]) ans[y] = i;
	}
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}