#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e3 + 10;
int a[maxn], b[maxn];
int main() {
	int Min = maxn;
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	for (int i = 0; i < n; i++) {
		scanf("%d", b + i);
		Min = min(Min, b[i] / a[i]);
	}
	int ans = Min;
	for (int i = 0; i < n; i++)
		b[i] -= a[i] * Min;
	while (k > 0) {
		int off = true;
		for (int i = 0; i < n; i++) {
			b[i] -= a[i];
			if (b[i] < 0) {
				k += b[i];
				b[i] = 0;
			}
			if (k < 0) {
				off = false;
				break;
			}
		}
		if (off)
			ans++;
	}
	printf("%d\n", ans);
	return 0;
}