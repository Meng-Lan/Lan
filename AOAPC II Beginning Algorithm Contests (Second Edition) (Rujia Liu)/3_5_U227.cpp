#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
const int maxn = 25;
char str[maxn][maxn];
int main() {
	int x, y;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			std::cin >> str[i][j];
			if (str[i][j] == '*')
				x = i, y = j;
		}
	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			printf("%c ", str[i][j]);
		putchar('\n');
	}*/
	char c;
	int ok;
	for (; scanf("%c", &c) && c - '0';) {
		ok = 0;
		if (c == 'A')
			if (x - 1 >= 0) {
				char temp = str[x - 1][y];
				str[x - 1][y] = str[x][y];
				str[x][y] = temp;
				x--;
			}
			else
				ok = 1;
		else if (c == 'B')
			if (x + 1 < 5) {
				char temp = str[x + 1][y];
				str[x + 1][y] = str[x][y];
				str[x][y] = temp;
				x++;
			}
			else
				ok = 1;
		else if (c == 'L')
			if (y - 1 >= 0) {
				char temp = str[x][y - 1];
				str[x][y - 1] = str[x][y];
				str[x][y] = temp;
				y--;
			}
			else
				ok = 1;
		else if (c == 'R')
			if (y + 1 < 5) {
				char temp = str[x][y + 1];
				str[x][y + 1] = str[x][y];
				str[x][y] = temp;
				y++;
			}
			else
				ok = 1;
		/*for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)
				printf("%c ", str[i][j]);
			putchar('\n');
		}
		putchar('\n');*/
		if (ok) {
			printf("This puzzle has no final configuration\n");
			break;
		}
	}
	if (!ok)
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)
				printf("%c ", str[i][j]);
			putchar('\n');
		}
	return 0;
}