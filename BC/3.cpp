#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
int main() {
	int t;
	scanf("%d\n", &t);
	char str[10];
	int a, b;
	while (t--) {
		scanf("%s", str);
		a = b = 0;
		for (int i = 0; i < 2; i++) {
			if (str[i] == 'T')
				a += 10;
			else if (str[i] == 'A')
				a += 1;
			else
				a += str[i] - '0';
		}
		for (int i = 2; i < 4; i++) {
			if (str[i] == 'T')
				b += 10;
			else if (str[i] == 'A')
				b += 1;
			else
				b += str[i] - '0';
		}
		if (a > b)
			if (21 - b - b + a < 6)
				printf("YES\n");
			else
				printf("NO\n");
		else
			if (21 - a - a + b < 7)
				printf("NO\n");
			else
				printf("YES\n");
	}
	return 0;
}