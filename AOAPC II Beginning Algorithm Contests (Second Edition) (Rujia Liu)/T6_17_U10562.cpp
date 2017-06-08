#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;

const int maxn = 200 + 10;
char buf[maxn][maxn];
int n;

void dfs(int r, int c) {
	printf("%c(", buf[r][c]);
	if (r + 1 < n&&buf[r + 1][c] == '|') {
		int i = c;
		while (i - 1 >= 0 && buf[r + 2][i - 1] == '-') i--;
		while (buf[r + 2][i] == '-'&&buf[r + 3][i] != '\0') {
			if (!isspace(buf[r + 3][i]))
				dfs(r + 3, i);
			i++;
		}
	}
	printf(")");
}

int main() {
	int T;
	fgets(buf[0], maxn, stdin);
	sscanf(buf[0], "%d", &T);
	while (T--) {
		n = 0;
		for (;;) {
			fgets(buf[n],maxn,stdin);
			if (buf[n][0] == '#')
				break;
			else
				n++;
		}
		printf("(");
		if (n) {
			int len = strlen(buf[0]);
			for (int i = 0; i < len; i++)
				if (buf[0][i] != ' ') {
					dfs(0, i);
					break;
				}
		}
		printf(")\n");
	}
	return 0;
}