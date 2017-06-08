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
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair

const int maxn = 25;
int n, Min,cnt, ans[5][maxn * 10];
char s[5][maxn];
bool pro[5][maxn];

bool check(int bgn) {
	FOR(i, n)
		FOR(j, 5)
		if (pro[j][i] && ans[j][i + bgn] != -1) return false;
	return true;
}

void draw(int bgn, int no) {
	FOR(i, n)
		FOR(j, 5)
		if (pro[j][i])
			ans[j][i + bgn] = no;
}

void dfs(int bgn,int no) {
	printf("%d\n", bgn);
	if (no == 10) {
		for (cnt = bgn + n;; --cnt) {
			FOR(i, 5) if (ans[i][cnt]) return;
		}
	}
	rep(i,0,n+1)
		if (check(i + bgn)) {
			Min = max(Min, i);
			draw(bgn+i, no);
			dfs(bgn+i, no + 1);
		}
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		memset(pro, 0, sizeof(pro)); Min = 0; memset(ans, -1, sizeof(ans));
		FOR(i, 5)
			scanf("%s", s[i]);
		FOR(i, 5)
			FOR(j, n)
			if (s[i][j] == 'X')	pro[i][j] = true;
		FOR(i, 5) {
			FOR(j, n)
				printf("%d", pro[i][j]);
			putchar('\n');
		}
		dfs(0, 0);
		printf("%d\n", cnt);
		FOR(i, 5) {
			For(j, cnt)
				printf("%c", ans[i][j]>=0?ans[i][j]+'0':'.');
			putchar('\n');
		}
	}
	return 0;
}