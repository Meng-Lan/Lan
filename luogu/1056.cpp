#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef pair<P, P> PP;
#define mp make_pair
const int maxd = 2000 + 5;

//此题输出是个坑，要求输出的从小到大排列

PP D[maxd];
P r[maxd], c[maxd];

bool cmp(const P &t, const P &s) {
	return t.first > s.first || t.first == s.first&&t.second < s.second;
}

int main() {
	int m, n, k, l, d;
	scanf("%d%d%d%d%d", &m, &n, &k, &l, &d);
	for (int i = 0; i < d; i++)
		scanf("%d%d%d%d", &D[i].first.first, &D[i].first.second, &D[i].second.first, &D[i].second.second);
	int len = max(m, n);
	for (int i = 1; i <= len; i++)
		r[i].second = c[i].second = i;
	for (int i = 0; i < d; i++)
		if (D[i].first.first != D[i].second.first)
			r[min(D[i].first.first, D[i].second.first)].first++;
		else
			c[min(D[i].first.second, D[i].second.second)].first++;
	sort(r, r + len + 1, cmp);
	sort(c, c + len + 1, cmp);
	vector<int> ans;
	for (int i = 0; i < k; i++) ans.push_back(r[i].second);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < k; i++) {
		if (i) putchar(' ');
		printf("%d", ans[i]);
	}
	putchar('\n');
	ans.clear();
	for (int i = 0; i < l; i++) ans.push_back(c[i].second);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < l; i++) {
		if (i) putchar(' ');
		printf("%d",ans[i]);
	}
	putchar('\n');
	return 0;
}