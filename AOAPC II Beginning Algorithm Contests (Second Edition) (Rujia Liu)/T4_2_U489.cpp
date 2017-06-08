#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#define maxn 100
int left, chance, win, lose;
char s[maxn], s2[maxn];
void guess(char c) {
	int bad = 1, len = strlen(s);
	for (int i = 0; i < len; i++)
		if (c == s[i]) {
			left--;
			s[i] = ' ';
			bad = 0;
		}
	if (bad)
		chance--;
	if (!left)
		win = 1;
	if (!chance)
		lose = 1;
}
int main() {
	int cnt;
	while (scanf("%d%s%s", &cnt, s, s2) && cnt != -1) {
		printf("Round %d\n", cnt);
		win = lose = 0;
		left = strlen(s);
		chance = 7;
		int len = strlen(s2);
		for (int i = 0; i < len; i++) {
			guess(s2[i]);
			if (win || lose)
				break;
		}
		if (win)
			printf("You win.\n");
		else if (lose)
			printf("You lose.\n");
		else
			printf("You chickened out.\n");
	}
	return 0;
}