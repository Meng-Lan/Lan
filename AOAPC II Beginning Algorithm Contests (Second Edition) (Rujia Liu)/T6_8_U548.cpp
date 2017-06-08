#include<iostream>
#include<string>
#include<algorithm>
#include<sstream>
using namespace std;

const int maxn = 1e4 + 10;
int in_order[maxn], post_order[maxn], lch[maxn], rch[maxn];
int n;
bool read_list(int *a) {
	string line;
	if (!getline(cin, line)) return false;
	stringstream ss(line);
	n = 0;
	int x;
	while (ss >> x) a[n++] = x;
	return n > 0;
}
int best, best_sum;
int build(int L1, int R1, int L2, int R2,int sum) {
	if (L1 > R1) return 0;
	int p = L1;
	int root = post_order[R2];
	sum += root;
	while (in_order[p] != root) p++;
	int cnt = p - L1;
	lch[root] = build(L1, p - 1, L2, L2 + cnt - 1,sum);
	rch[root] = build(p + 1, R1, L2 + cnt, R2 - 1,sum);
	if(!lch[root]&&!rch[root])
		if (sum < best_sum || sum == best_sum&&root < best) {
			best = root;
			best_sum = sum;
		}
	return root;
}
void dfs(int u,int sum) {
	sum += u;
	if (!lch[u] && !rch[u]) {
		if (sum < best_sum || sum == best_sum&&u < best) {
			best = u;
			best_sum = sum;
		}
	}
	if (lch[u]) dfs(lch[u], sum);
	if (rch[u]) dfs(rch[u], sum);
}
int main() {
	while (read_list(in_order)) {
		read_list(post_order);
		best_sum = 1e9;
		build(0, n - 1, 0, n - 1,0);
		cout << best << endl;
	}
	return 0;
}