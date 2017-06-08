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
#define mp make_pair
const int maxn = 5e3 + 5;

P lan[maxn];

bool cmp(const P &s, const P &t) {
	return s.second > t.second || s.second == t.second&&s.first < t.first;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d%d", &lan[i].first, &lan[i].second);
	sort(lan, lan + n, cmp);
	int len = m*1.5;
	int ans = lan[len-1].second;
	for (; len < n&& lan[len - 1].second == lan[len].second; len++);
	printf("%d %d\n", ans, len);
	for (int i = 0; i < len; i++)
		printf("%d %d\n", lan[i].first, lan[i].second);
	return 0;
}