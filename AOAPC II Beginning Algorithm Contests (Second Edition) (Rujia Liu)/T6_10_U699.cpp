#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1e5 + 10;
int sum[maxn];
void build(int p) {
	int v;
	cin >> v;
	if (v == -1) return;
	sum[p] += v;
	build(p - 1);
	build(p + 1);
}
bool init() {
	int v;
	cin >> v;
	if (v == -1) return false;
	int p = maxn / 2;
	memset(sum, 0, sizeof(sum));
	sum[p] += v;
	build(p - 1);
	build(p + 1);
	return true;
}
int main() {
	int kase = 0;
	while (init()) {
		int p = 0;
		while (!sum[p]) p++;
		cout << "Case " << ++kase << ":\n" << sum[p++];
		while (sum[p]) cout << " " << sum[p++];
		putchar('\n');
		putchar('\n');
	}
	return 0;
}