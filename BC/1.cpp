#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
int num[1005][1005];
int main() {
	int t;
	scanf("%d", &t);
	int n, m;
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &num[i][j]);
		int off = 1;
		if (n % 2 == 0 && m % 2 == 0)
			if (num[n - 2][m - 1] == 0 && num[n - 1][m - 2] == 0)
				off = 0;
		if (off)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}