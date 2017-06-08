#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
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
const int maxn = 100000 + 10;
char s[maxn];
int k, n;
int bgn = 0, end = 0, Max = 0;
void find(char c) {
	bgn = 0;
	queue<int> q;
	for (int i = 0; i < n; i++) {
		if (s[i] == c)
			if (q.size() >= k) {
				while (q.size() > k) {
					bgn = q.front(); q.pop();
				}
				Max = max(Max, i - bgn);
				if (q.size() >= 1) {
					bgn = q.front();
					q.pop();
				}
				else
					bgn = 0;
				q.push(i + 1);
			}
			else
				q.push(i + 1);
	}
	if (c == 'a'&&s[n - 1] == 'b')
		Max = max(Max, n - bgn);
	else if (c == 'b'&&s[n - 1] == 'a')
		Max = max(Max, n - bgn);
}
int main() {
	scanf("%d%d %s", &n, &k, s);
	int a = 0, b = 0;
	for (int i = 0; i < n; ++i)
		if (s[i] == 'a')
			++a;
		else
			++b;
	if (a <= k || b <= k) {
		printf("%d\n", n);
		return 0;
	}
	find('a');
	find('b');
	printf("%d\n", Max);
	return 0;
}