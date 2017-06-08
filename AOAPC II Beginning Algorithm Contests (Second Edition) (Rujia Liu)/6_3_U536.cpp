#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
string pre_order, in_order;
void post_order(int L1, int R1, int L2, int R2) {
	if (L1 > R1) return;
	char root = pre_order[L1];
	int m = L2;
	while (in_order[m] != root) m++;
	int cnt = m - L2;
	post_order(L1 + 1, L1 + cnt, L2, m - 1);
	post_order(L1 + cnt + 1, R1, m + 1, R2);
	putchar(root);
}
int main() {
	while (cin >> pre_order) {
		cin >> in_order;
		post_order(0, pre_order.size() - 1, 0, in_order.size() - 1);
		putchar('\n');
	}
	return 0;
}