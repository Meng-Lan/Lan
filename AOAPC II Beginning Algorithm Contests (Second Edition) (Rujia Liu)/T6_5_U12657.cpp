#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int Left[maxn], Right[maxn];
inline void link(int L, int R) {
	Right[L] = R;
	Left[R] = L;
}
int main() {
	int kase = 0, n, m;
	while (scanf("%d%d", &n, &m)==2) {
		for (int i = 1; i <= n; i++) {
			Left[i] = i - 1;
			Right[i] = (i + 1) % (n + 1);
		}
		Left[0] = n;
		Right[0] = 1;
		int inv = 0, op, x, y;
		while (m--) {
			scanf("%d", &op);
			if (op == 4) inv = !inv;
			else {
				scanf("%d%d", &x, &y);
				if (op == 3 && Right[y] == x) swap(x, y);
				if (op != 3 && inv) op = 3 - op;
				if (op == 1 && x == Left[y]) continue;
				if (op == 2 && x == Right[y]) continue;
				int Rx = Right[x], Lx = Left[x], Ry = Right[y], Ly = Left[y];
				if (op == 1) {
					link(Lx, Rx);
					link(Ly, x);
					link(x, y);
				}
				else if (op == 2) {
					link(Lx, Rx);
					link(y, x);
					link(x, Ry);
				}
				else if (op == 3) {
					if (Right[x] == y) {
						link(Lx, y);
						link(y, x);
						link(x, Ry);
					}
					else {
						link(Ly, x);
						link(x, Ry);
						link(Lx, y);
						link(y, Rx);
					}
				}
			}
		}
		int b = 0;
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			b = Right[b];
			if (i & 1)
				ans += b;
		}
		if (inv&&n % 2 == 0)
			ans = (long long)n*(n + 1) / 2 - ans;
		printf("Case %d: %lld\n", ++kase, ans);
	}
	return 0;
}