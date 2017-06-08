#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e3;
int main() {
	int T = 15;
	printf("1\n");
	int n = maxn, m = maxn, q = 100000;
	printf("%d %d %d\n", n, m, q);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++)
			printf("%d ", maxn);
		printf("%d\n", maxn);
	}
	for (int i = 0; i < q; i++)
		printf("1 1 999\n");
	return 0;
}