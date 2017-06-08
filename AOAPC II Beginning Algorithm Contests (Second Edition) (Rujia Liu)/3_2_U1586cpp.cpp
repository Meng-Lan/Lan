#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<iostream>
#include<cstdio>
const int maxn = 100;
char str[maxn];
enum lan { C = 0, H = 1, O = 2, N = 3 };
double num[4] = { 12.01,1.008,16.00,14.01 };
int getint(int n, int len) {
	int temp = 0;
	for (int i = n; str[i] >= '0'&&str[i] <= '9'; i++) {
		temp *= 10;
		temp += str[i] - '0';
	}
	return temp;
}
int main() {
	scanf("%s", str);
	int len = strlen(str);
	int temp;
	double ans = 0.0;
	for (int i = 0; i < len; i++) {
		temp = 1;
		if (str[i] == 'C') {
			if (str[i + 1] >= '0'&&str[i + 1] <= '9')
				temp = getint(i + 1, len);
			ans += num[C] * temp;
		}
		if (str[i] == 'H') {
			if (str[i + 1] >= '0'&&str[i + 1] <= '9')
				temp = getint(i + 1, len);
			ans += num[H] * temp;
		}
		if (str[i] == 'O') {
			if (str[i + 1] >= '0'&&str[i + 1] <= '9')
				temp = getint(i + 1, len);
			ans += num[O] * temp;
		}
		if (str[i] == 'N') {
			if (str[i + 1] >= '0'&&str[i + 1] <= '9')
				temp = getint(i + 1, len);
			ans += num[N] * temp;
		}
		//printf("%f\n", ans);
	}
	printf("%.3f\n", ans);
	return 0;
}