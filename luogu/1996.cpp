#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
int num[105];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		num[i] = i + 1;
	}
	/*for (int i = 0; i < n; i++)
		printf("%d ", num[i]);*/
	int p = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (;;)
				if (num[(++p)%n] == 0)
					;
				else
					break;
		}
		printf("%d ", num[p%n]);
		num[p%n] = 0;
	}
	return 0;
}