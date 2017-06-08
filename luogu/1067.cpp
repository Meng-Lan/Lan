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
P ans[105];
int n;

void print(int top) {
	if (top != n&&!ans[top].first)
		putchar('+');
	if (ans[top].first)
		putchar('-');
	if (top&&ans[top].second != 1)
		printf("%d", ans[top].second);
	if (!top)
		printf("%d", ans[top].second);
	if (top) putchar('x');
	if (top&&top != 1)
		printf("^%d", top);
}

int main() {
	scanf("%d", &n);
	for (int i = n; i >= 0; --i)
		scanf("%d", &ans[i].second);
	for (int i = 0; i <= n; ++i)
		if (ans[i].second < 0) {
			ans[i].first = 1;
			ans[i].second *= -1;
		}
	for (int i = n; i >= 0; --i)
		if (ans[i].second)
			print(i);
	putchar('\n');
	return 0;
}