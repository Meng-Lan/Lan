#include<cstdio>
#include<cstring>
const int maxn = 1e2 + 5;
char pic[maxn][maxn];
int ide[maxn][maxn], n, m;
void dfs(int r, int c, int cnt) {
	if (r < 0 || r >= m || c < 0 || c >= n) return;
	if (ide[r][c] > 0 || pic[r][c] != '@') return;
	ide[r][c] = cnt;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (i != 0 || j != 0) dfs(r + i, c + j, cnt);
}
int main() {
	while (scanf("%d%d", &m, &n) && n&&m) {
		for (int i = 0; i < m; i++)
			scanf("%s", pic[i]);
		memset(ide, 0, sizeof(ide));
		int cnt = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (ide[i][j] == 0 && pic[i][j] == '@')
					dfs(i, j, ++cnt);
		printf("%d\n", cnt);
	}
	return 0;
}