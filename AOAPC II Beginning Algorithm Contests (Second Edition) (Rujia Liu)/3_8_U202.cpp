#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
//#include<new>
#include<iostream>
const int maxn = 3003;
int num[maxn], r[maxn];
int main() {
	int a, b;
	while (scanf("%d%d", &a, &b)) {
		memset(num, 0, sizeof num);
		memset(r, 0, sizeof r);
		int count = 0;
		printf("%d/%d=", a, b);
		num[count++] = a / b;
		a %= b;
		while (!r[a] && a) {
			r[a] = count;
			num[count++] = a * 10 / b;
			a = a * 10 % b;
		}
		printf("%d.", num[0]);
		for (int i = 1; i < count&&i < 50; i++) {
			if (a&&r[a] == i)
				printf("(");
			printf("%d", num[i]);
		}
		if (!a) printf("(0");
		if (count > 50)
			printf("...");
		printf(")\n");
		printf("   %d = number of digits in repeating cycle\n\n", !a ? 1 : count - r[a]);
	}
	return 0;
}