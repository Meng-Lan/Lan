#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
int num[105];
int main() {
	for (int i = 0; i < 105; i++)
		num[i] = i + 1;
	int n, m;
	scanf("%d%d", &n, &m);
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i ? 0 : 1; j < m; )
			if (num[count%n] != 0) {
				count++;
				j++;
			}
			else
				count++;
		for (;;)
			if (num[count%n] != 0) {
				printf("%d ", num[count%n]);
				num[count%n] = 0;
				break;
			}
			else
				for (;;)
					if (num[count%n] == 0)
						count++;
					else
						break;
	}
	printf("....");
	return 0;
}