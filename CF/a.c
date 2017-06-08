#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main() {
	int a, b, c, x, y, z;
	scanf("%d%d%d", &a, &b, &c);
	scanf("%d%d%d", &x, &y, &z);
	int temp = 0;
	if (a > x)
		temp += a - x;
	if (b > y)
		temp += b - y;
	if (c > z)
		temp += c - z;
	if (a < x)
		temp -= 2 * (x - a);
	if (b < y)
		temp -= 2 * (y - b);
	if (c < z)
		temp -= 2 * (z - c);
	if (temp >= 0)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}