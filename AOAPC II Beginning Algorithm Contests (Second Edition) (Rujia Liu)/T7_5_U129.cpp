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
const int maxn = 100;
int S[maxn],n,L,cnt;
int dfs(int cur) {
	if (cnt++ == n) {
		for (int i = 0; i < cur; i++) {
			if (i&&i % 64 == 0) putchar('\n');
			else if (i&&i % 4 == 0) putchar(' ');
			printf("%c", 'A' + S[i]);
		}
		printf("\n%d\n", cur);
		return 0;
	}
	for (int i = 0; i < L; i++) {
		S[cur] = i;
		int ok = 1;
		for (int j = 1; j * 2 <= cur + 1; j++) {
			int equal = 1;
			for (int k = 0; k < j; k++)
				if (S[cur - k] != S[cur - j - k]) {
					equal = 0;
					break;
				}
			if (equal) {
				ok = 0;
				break;
			}
		}
		if (ok)
			if (!dfs(cur + 1))
				return 0;
	}
	return 1;
}
int main() {
	while (scanf("%d%d", &n, &L)&&n) {
		cnt = 0;
		dfs(0);
	}
	return 0;
}