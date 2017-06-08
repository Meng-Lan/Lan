#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
int main() {
	char str[] = "nubtqphsoe";
	int a, b, c, n;
	while (scanf("%d", &n) != EOF) {
		a = n % 10;
		n /= 10;
		b = n % 10;
		n /= 10;
		c = n;
		printf("%c%c%c\n", str[c] + 'A' - 'a', str[b], str[a]);
	}
	return 0;
}