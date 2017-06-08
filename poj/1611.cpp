#include<iostream>
#include<cstdio>
const int maxn = 3e4 + 10;
int par[maxn],n,m;
int get_par(int a) {
	if (par[a] != a)
		par[a] = get_par(par[a]);
	return par[a];
}
void merge(int a, int b) {
	par[get_par(a)] = get_par(b);
}
bool query(int a, int b) {
	return get_par(a) == get_par(b);
}
int main() {
	while (scanf("%d%d", &n, &m)==2) {
		for (int i = 0; i < n; i++)
			par[i] = i;
		while (m--) {
			int T;
			scanf("%d", &T);
			int a, b;
			scanf("%d", &a);
			while (--T) {
				scanf("%d", &b);
				merge(a, b);
			}
		}
		int ans = 1;
		for (int i = 1; i < n; i++)
			if (query(par[0], par[i]))
				ans++;
		printf("%d\n", ans);
	}
	return 0;
}