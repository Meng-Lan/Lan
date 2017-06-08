#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1e3 + 5;
int num[maxn][maxn];
int *r[maxn], c[maxn];
int rn[maxn], cn[maxn];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(num, 0, sizeof(num));
		memset(r, 0, sizeof(r));
		memset(c, 0, sizeof(c));
		memset(rn, 0, sizeof(rn));
		memset(cn, 0, sizeof(cn));
		int n, m, q;
		scanf("%d%d%d", &n, &m, &q);
		int op, x, y;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &num[i][j]);
		for (int i = 0; i < n; i++) {
			r[i] = num[i];
		}
		for (int j = 0; j < m; j++) {
			c[j] = j;
		}
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) {
				swap(r[x - 1], r[y - 1]);
				swap(rn[x - 1], rn[y - 1]);
			}
			else if (op == 2) {
				swap(c[x - 1], c[y - 1]);
				swap(cn[x - 1], cn[y - 1]);
			}
			else if (op == 3)
				rn[x - 1] += y;
			else if (op == 4)
				cn[x - 1] += y;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d", *(r[i] + c[j]) + rn[i] + cn[j]);
				if (j != m - 1)
					putchar(' ');
			}
			putchar('\n');
		}
	}
	return 0;
}