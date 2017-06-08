#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<iostream>
//差被将吃一字的判断
struct Lan {
	int x, y;
	char s[10];
}lan[10];
bool pq[11][10], p[11][10];
int main() {
	int x, y, n;
	while (scanf("%d%d%d", &n, &x, &y) == 3 && n) {
		memset(pq, 0, sizeof(pq));
		memset(p, 0, sizeof(p));
		int off = 1, wtf;
		for (int i = 0; i < n; i++) {
			scanf("%s%d%d", lan[i].s, &lan[i].x, &lan[i].y);
			p[lan[i].x][lan[i].y] = true;
			if (strcmp(lan[i].s, "G") == 0)
				wtf = i;
		}
		if (lan[wtf].y == y) {
			int iiii = 0;
			for (int i = x+1; i < lan[wtf].x; i++)
				if (p[i][y])
					iiii++;
			if (!iiii)
				off = 0;
		}
		/*for (int i = 0; i < n; i++)
			printf("%s\n", lan[i].s);*/
		for (int k = 0; k < n; k++) {
			memset(pq, 0, sizeof(pq));
			int sta = 0;
			if (x - 1 >= 1 && lan[k].x == x - 1 && lan[k].y == y)
				sta = 1;
			if (x + 1 <= 3 && lan[k].x == x + 1 && lan[k].y == y)
				sta = 1;
			if (y - 1 >= 4 && lan[k].x == x&& lan[k].y == y - 1)
				sta = 1;
			if (y + 1 <= 6 && lan[k].x == x&& lan[k].y == y + 1)
				sta = 1;
			int tempx, tempy;
			if (sta) {
				p[lan[k].x][lan[k].y] = false;
				tempx = x;
				tempy = y;
				x = lan[k].x;
				y = lan[k].y;
			}
			for (int i = 0; i < n; i++) {
				if (sta&&i==k)
					continue;
				if (strcmp(lan[i].s, "G") == 0)
					for (int j = lan[i].x - 1; j >= 1; j--) {
						if (p[j][lan[i].y])
							break;
						pq[j][lan[i].y] = true;
					}
				if (strcmp(lan[i].s, "R") == 0) {
					//printf("R***\n");
					for (int j = 1; j <= 10; j++)
						pq[j][lan[i].y] = true;
					for (int j = 1; j <= 9; j++)
						pq[lan[i].x][j] = true;
				}
				if (strcmp(lan[i].s, "H") == 0) {
					//printf("H---\n");
					int xx = lan[i].x, yy = lan[i].y;
					if (xx + 1 <= 10 && p[xx + 1][yy] == false) {
						if (xx + 2 <= 10 && yy + 1 <= 9)
							pq[xx + 2][yy + 1] = true;
						if (xx + 2 <= 10 && yy - 1 >= 1)
							pq[xx + 2][yy - 1] = true;
					}
					if (xx - 1 >= 1 && p[xx - 1][yy] == false) {
						if (xx - 2 >= 1 && yy + 1 <= 9)
							pq[xx - 2][yy + 1] = true;
						if (xx - 2 >= 1 && yy - 1 >= 1)
							pq[xx - 2][yy - 1] = true;
					}
					if (yy + 1 <= 9 && p[xx][yy + 1] == false) {
						if (xx + 1 <= 10 && yy + 2 <= 9)
							pq[xx + 1][yy + 2] = true;
						if (xx - 1 >= 1 && yy + 2 <= 9)
							pq[xx - 1][yy + 2] = true;
					}
					if (yy - 1 >= 1 && p[xx][yy - 1] == false) {
						if (yy - 2 >= 1 && xx + 1 <= 9)
							pq[xx + 1][yy - 2] = true;
						if (yy - 2 >= 1 && xx - 1 >= 1)
							pq[xx - 1][yy - 2] = true;
					}
				}
				if (strcmp(lan[i].s, "C") == 0) {
					//printf("C+++\n");
					int xx = lan[i].x, yy = lan[i].y;
					int temp = 0;
					for (int j = xx + 1; j <= 10; j++) {
						if (p[j][yy])
							if (temp)
								break;
							else
								temp = j;
						if (temp)
							pq[j][yy] = true;
					}
					temp = 0;
					for (int j = xx - 1; j >= 1; j--) {
						if (p[j][yy])
							if (temp)
								break;
							else
								temp = j;
						if (temp)
							pq[j][yy] = true;
					}
					temp = 0;
					for (int j = yy + 1; j <= 9; j++) {
						if (p[xx][j])
							if (temp)
								break;
							else
								temp = j;
						if (temp)
							pq[xx][j] = true;
					}
					temp = 0;
					for (int j = yy - 1; j >= 1; j--) {
						if (p[xx][j])
							if (temp)
								break;
							else
								temp = j;
						if (temp)
							pq[xx][j] = true;
					}
				}
			}
			if (pq[x][y] == false)
				off = 0;
			else {
				if (x - 1 >= 1 && pq[x - 1][y] == false)
					off = 0;
				if (x + 1 <= 3 && pq[x + 1][y] == false)
					off = 0;
				if (y - 1 >= 4 && pq[x][y - 1] == false)
					off = 0;
				if (y + 1 <= 6 && pq[x][y + 1] == false)
					off = 0;
			}
			if (sta) {
				p[lan[k].x][lan[k].y] = true;
				x = tempx;
				y = tempy;
			}
			if (!off)
				break;
			/*for (int i = 1; i <= 10; i++) {
				printf("%d# ", i);
				for (int j = 1; j <= 9; j++)
					printf("%d ", pq[i][j]);
				putchar('\n');
			}*/
		}
		if (off)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
/*
2 1 4
G 10 5
R 6 4

3 1 5
H 4 5
G 10 5
C 7 5

0 0 0
*/