#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
int num[10];
int main() {
	int n, temp;
	scanf("%d", &n);
	num[0]++;
	for (int i = 1; i <= n; i++) {
		temp = i;
		while (temp) {
			num[temp % 10]++;
			temp /= 10;
		}
	}
	for (int i = 0; i < n; i++)
		printf("%d:%d  ", i, num[i]);
	return 0;
}