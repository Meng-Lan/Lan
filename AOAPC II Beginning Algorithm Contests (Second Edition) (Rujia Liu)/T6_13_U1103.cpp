#include<iostream>
#include<cstdio>
#include<set>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

char bin[1 << 8][5];
const int maxw = 200 + 5;
const int maxh = 200 + 5;

int H, W, pic[maxh][maxw], color[maxh][maxw];
char line[maxw];

void decode(int i, int j, char ch) {
	for (int k = 0; k < 4; k++)
		pic[i][j + k] = bin[ch][k]-'0';
}

const int dr[] = { -1,1,0,0 };
const int dc[] = { 0,0,-1,1 };

void dfs(int i, int j,int cnt) {
	color[i][j] = cnt;
	for (int k = 0; k < 4; k++) {
		int r = i + dr[k];
		int c = j + dc[k];
		if (r >= 0 && r < H&&c >= 0 && c < W&&pic[r][c] == pic[i][j] && !color[r][c])
			dfs(r, c, cnt);
	}
}

vector<set<int> > neighbors;
void check_neighbors(int r, int c) {
	for (int i = 0; i < 4; i++) {
		int r1 = r + dr[i];
		int c1 = c + dc[i];
		if (r1 >= 0 && r1 < H&&c1 >= 0 && c1 < W&&color[r1][c1] != 1 && pic[r1][c1] == 0)
			neighbors[color[r][c]].insert(color[r1][c1]);
	}
}

const char *code = "WAKJSD";
int recognize(int c) {
	int cnt = neighbors[c].size();
	return code[cnt];
}

int main() {
	strcpy(bin['0'], "0000");
	strcpy(bin['1'], "0001");
	strcpy(bin['2'], "0010");
	strcpy(bin['3'], "0011");
	strcpy(bin['4'], "0100");
	strcpy(bin['5'], "0101");
	strcpy(bin['6'], "0110");
	strcpy(bin['7'], "0111");
	strcpy(bin['8'], "1000");
	strcpy(bin['9'], "1001");
	strcpy(bin['a'], "1010");
	strcpy(bin['b'], "1011");
	strcpy(bin['c'], "1100");
	strcpy(bin['d'], "1101");
	strcpy(bin['e'], "1110");
	strcpy(bin['f'], "1111");
	int kase = 0;
	while (scanf("%d%d", &H, &W)==2 && H&&W) {
		memset(pic, 0, sizeof(pic));
		for (int i = 0; i < H; i++) {
			scanf("%s", line);
			for (int j = 0; j < W; j++)
				decode(i + 1, j * 4 + 1, line[j]);
		}

		int cnt = 0;
		W = W * 4 + 2;
		H += 2;
		memset(color, 0, sizeof(color));
		vector<int> cc;
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				if (!color[i][j]) {
					dfs(i, j, ++cnt);
					if (pic[i][j] == 1)
						cc.push_back(cnt);
				}
		neighbors.clear();
		neighbors.resize(cnt + 2);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				if (pic[i][j])
					check_neighbors(i, j);
		vector<char> ans;
		for (int i = 0; i < cc.size(); i++)
			ans.push_back(recognize(cc[i]));
		sort(ans.begin(), ans.end());

		printf("Case %d: ", ++kase);
		for (int i = 0; i < ans.size(); i++)
			printf("%c", ans[i]);
		putchar('\n');
	}
	return 0;
}