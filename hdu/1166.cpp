#include<iostream>
#include<cstdio>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int maxn = 5e4 + 10;
int sum[maxn << 2];
void pushUP(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void build(int l,int r,int rt) {
	if (l == r) {
		scanf("%d", sum + rt);
		return;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushUP(rt);
}
int query(int L,int R,int l,int r,int rt) {
	if (l >= L&&r <= R)
		return sum[rt];
	int res = 0;
	int m = (l + r) >> 1;
	if (L <= m)
		res += query(L, R, lson);
	if (m < R)
		res += query(L, R, rson);
	return res;
}
void updata(int p,int add,int l,int r,int rt) {
	if (l == r) {
		sum[rt] += add;
		return;
	}
	int m = (l + r) >> 1;
	if (p <= m)
		updata(p, add, lson);
	else
		updata(p, add, rson);
	pushUP(rt);
}
int main() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		printf("Case %d:\n", i);
		int n;
		cin >> n;
		build(1, n, 1);
		char s[10];
		while (scanf("%s", s)) {
			if (s[0] == 'E')
				break;
			int a, b;
			scanf("%d%d", &a, &b);
			if (s[0] == 'Q') printf("%d\n", query(a,b,1,n,1));
			else if (s[0] == 'S') updata(a, -b, 1, n, 1);
			else if (s[0] == 'A') updata(a, b, 1, n, 1);
		}
	}
	return 0;
}