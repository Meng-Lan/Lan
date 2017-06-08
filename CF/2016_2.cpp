#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#define maxn 55
int num[maxn][maxn];
int p[maxn];
int min(int x, int y) {
	if (x <= y)
		return x;
	else
		return y;
}
int main() {
	int n;
	std::cin >> n;
	/*for (int i = 0; i < maxn; i++)
		p[i] = max;*/
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &num[i][j]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (p[j] < num[i][j])
				p[j] = num[i][j];
	int max = 0;
	for (int i = 0; i < n; i++)
		if (p[i]>max)
			max = p[i];
	for (int i = 0; i < n;i++)
		if (p[i] == max) {
			p[i]++;
			break;
		}
	int ok = 0;
	for (int i = 0; i < n; i++) {
		if (ok++)
			std::cout << " ";
		std::cout << p[i];
	}
	std::cout << std::endl;
	return 0;
}