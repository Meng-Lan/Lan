#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 100;
char buf[maxn];
int main() {
	int n, kase = 0;
	while (scanf("%d", &n) && n) {
		if (kase++)
			putchar('\n');
		int cnt = 0;
		for (int fghij = 1234;; fghij++) {
			int abcde = fghij*n;
			sprintf(buf, "%05d%05d", abcde, fghij);
			if (strlen(buf) > 10) break;
			sort(buf, buf + 10);
			int ok = 1;
			for (int i = 0; i < 10; i++)
				if (buf[i] - '0' != i) {
					ok = 0;
					break;
				}
			if (ok) {
				cnt++;
				printf("%05d / %05d = %d\n", abcde, fghij, n);
			}
		}
		if (!cnt)
			printf("There are no solutions for %d.\n", n);
	}
	return 0;
}