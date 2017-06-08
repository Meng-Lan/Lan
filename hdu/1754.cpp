#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int maxn = 2e5 + 10;
int MAX[maxn << 2];
void pushUP(int rt) {
	MAX[rt] = max(MAX[rt << 1], MAX[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
	if (l == r) {
		scanf("%d", MAX + rt);
		return;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushUP(rt);
}
void UpData(int p, int t,int l,int r,int rt) {
	if (l == r) {
		MAX[rt] = t;
		return;
	}
	int m = (l + r) >> 1;
	if (p<=m)
		UpData(p, t, lson);
	else
		UpData(p, t, rson);
	pushUP(rt);
}
int query(int L,int R,int l,int r,int rt) {
	if (l >= L&&r <= R) {
		return MAX[rt];
	}
	int res = 0;
	int m = (l + r) >> 1;
	if (m >= L)
		res=max(res,query(L, R, lson));
	if (m < R)
		res=max(res,query(L, R, rson));
	return res;
}
int main() {
	int n, m;
	while (cin >> n >> m) {
		build(1, n, 1);
		char op[3];
		int a, b;
		while (m--) {
			scanf("%s%d%d", op, &a, &b);
			if (op[0] == 'Q')
				printf("%d\n", query(a, b, 1, n, 1));
			else
				UpData(a, b,1,n,1);
		}
	}
	return 0;
}