#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int maxn = 5e3 + 10;
int sum[maxn << 2];
void pushUP(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void build(int l, int r, int rt) {
	sum[rt] = 0;
	if(l==r) return;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}
void updata(int x, int l, int r, int rt) {
	if (l == r) {
		sum[rt]++;
		return;
	}
	int m = (l + r) >> 1;
	if (m >= x)
		updata(x, lson);
	else
		updata(x, rson);
	pushUP(rt);
}
int query(int L, int R, int l, int r, int rt) {
	if (l >= L&&r <= R) {
		return sum[rt];
	}
	int m = (l + r) >> 1;
	int res = 0;
	if (m >= L)
		res += query(L, R, lson);
	if (m < R)
		res += query(L, R, rson);
	return res;
}
int t[maxn];
int main() {
	int n;
	while (cin >> n) {
		build(0, n - 1, 1);
		int sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", t + i);
			sum += query(t[i], n - 1, 0, n - 1, 1);
			updata(t[i], 0, n - 1, 1);
		}
		int ans = sum;
		for (int i = 0; i < n; i++) {
			sum += n - t[i] - t[i] - 1;
			ans = min(sum, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}