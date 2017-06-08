#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 2e5 + 10;
int MAX[maxn << 2];
int h, w, n;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
void pushUP(int rt) {
	MAX[rt] = max(MAX[rt << 1], MAX[rt << 1 | 1]);
}
void updata() {

}
void build(int l, int r, int rt) {
	MAX[rt] = w;
	if (l == r)
		return;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}
int query(int t,int l,int r,int rt) {
	if (l == r) {
		MAX[rt] -= t;
		return l;
	}
	int m = (l + r) >> 1;
	int res=MAX[rt << 1] >= t ? query(t, lson) : query(t,rson);
	pushUP(rt);
	return res;
}
int main() {
	while (cin >> h >> w >> n) {
		if (h > n)
			h = n;
		build(1, h, 1);
		int x;
		while (n--) {
			scanf("%d", &x);
			if (MAX[1] < x)
				puts("-1");
			else
				printf("%d\n", query(x,1,h,1));
		}
	}
	return 0;
}