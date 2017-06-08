#include<iostream>
#include<cstdio>
#include<cstring>
const int maxn = 1 << 10 + 10;
const int len = 1 << 5;
char s[maxn];
int buf[len][len];
int cnt;
void draw(const char *s, int &p, int c, int r, int w) {
	char ch = s[p++];
	if (ch == 'p') {
		draw(s, p, c + w / 2, r, w / 2);
		draw(s, p, c, r, w / 2);
		draw(s, p, c, r + w / 2, w / 2);
		draw(s, p, c + w / 2, r + w / 2, w / 2);
	}
	else if (ch == 'f') {
		for (int i = r; i < r + w; i++)
			for (int j = c; j < c + w; j++)
				if (buf[i][j] == 0) {
					buf[i][j] = 1;
					cnt++;
				}
	}
}
int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(buf, 0, sizeof(buf));
		cnt = 0;
		for (int i = 0; i < 2; i++) {
			std::cin >> s;
			int p = 0;
			draw(s, p, 0, 0, len);
		}
		printf("There are %d black pixels.\n", cnt);
	}
	return 0;
}