#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int maxn = 60;
const int mid = 30;
int G[maxn][maxn], c[maxn];
int n;
char s[maxn];

void buildG(int &i, int &j, int &k, int &l) {
	if (j != mid)
		G[i][j] = 1;
	if (k != mid)
		G[i][k] = 1;
	if (l != mid)
		G[i][l] = 1;
}

bool dfs(int u) {
	c[u] = -1;
	for (int i = 1; i < maxn;i++)
		if (G[u][i]) {
			//cout << u << "  " << i << endl;
			//cout << maxn - i << endl;
			if (c[maxn-i] < 0) return true;
			if (!c[maxn-i] && dfs(maxn-i)) return true;
		}
	c[u] = 1;
	return false;
}

bool topsort() {
	memset(c, 0, sizeof(c));
	for (int i = 0; i < maxn; i++)
		if (!c[i])
			if (dfs(i)) return true;
	return false;
}

int main() {
	while (scanf("%d", &n)!=EOF && n) {
		memset(G, 0, sizeof(G));
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			int t[4] = {};
			for (int j = 0; j < 4; j++)
				if (s[j << 1] == '0')
					t[j] = mid;
				else {
					if (s[j << 1 | 1] == '+')
						t[j] = (s[j << 1] - 'A') + mid + 1;
					else
						t[j] = mid - (s[j << 1] - 'A') - 1;
				}
				if (t[0] != mid)
					buildG(t[0], t[1], t[2], t[3]);
				if (t[1] != mid)
					buildG(t[1], t[0], t[2], t[3]);
				if (t[2] != mid)
					buildG(t[2], t[0], t[1], t[3]);
				if (t[3] != mid)
					buildG(t[3], t[0], t[1], t[2]);
		}
		/*for (int i = 0; i < maxn; i++)
			for (int j = 0; j < maxn; j++)
				if (G[i][j])
					cout << i << "  " << j << endl;
		putchar('\n');*/
		if (topsort())
			printf("unbounded\n");
		else
			printf("bounded\n");
	}
	return 0;
}