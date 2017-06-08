#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
const int maxn = 10000;
struct Lan {
	char cmd[10];
	int r1, r2, c1, c2, a, x[20];
}lan[maxn];
int r, c, n;
bool simulate(int *r0, int *c0) {
	for (int i = 0; i < n; i++) {
		if (lan[i].cmd[0] == 'E') {
			if (lan[i].r1 == *r0&&lan[i].c1 == *c0) {
				*r0 = lan[i].r2;
				*c0 = lan[i].c2;
			}
			else if (lan[i].r2 == *r0&&lan[i].c2 == *c0) {
				*r0 = lan[i].r1;
				*c0 = lan[i].c1;
			}
		}
		else {
			int dr = 0, dc = 0;
			for (int j = 0; j < lan[i].a; j++) {
				int temp = lan[i].x[j];
				if (lan[i].cmd[0] == 'I') {
					if (lan[i].cmd[1] == 'R'&&temp <= *r0)
						dr++;
					if (lan[i].cmd[1] == 'C'&&temp <= *c0)
						dc++;
				}
				else {
					if (lan[i].cmd[1] == 'R'&&temp == *r0) return false;
					if (lan[i].cmd[1] == 'C'&&temp == *c0) return false;
					if (lan[i].cmd[1] == 'R'&&temp < *r0) dr--;
					if (lan[i].cmd[1] == 'C'&&temp < *c0) dc--;
				}
			}
			*r0 += dr;
			*c0 += dc;
		}
	}
	return true;
}
int main() {
	int r0, c0, kase = 0, q;
	while (scanf("%d%d%d", &r, &c, &n) == 3 && r) {
		for (int i = 0; i < n; i++) {
			scanf("%s", lan[i].cmd);
			if (lan[i].cmd[0] == 'E')
				scanf("%d%d%d%d", &lan[i].r1, &lan[i].c1, &lan[i].r2, &lan[i].c2);
			else {
				scanf("%d", &lan[i].a);
				for (int j = 0; j < lan[i].a; j++)
					scanf("%d", &lan[i].x[j]);
			}
		}
		if (kase > 0) putchar('\n');
		printf("Spreadsheet #%d\n", ++kase);
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d", &r0, &c0);
			printf("Cell data in (%d,%d) ", r0, c0);
			if (simulate(&r0, &c0))
				printf("moved to (%d,%d)\n", r0, c0);
			else
				printf("GONE\n");
		}
	}
	return 0;
}
/*
7 9
5
DR 2 1 5
DC 4 3 6 7 9
IC 1 3
IR 2 2 4
EX 1 2 6 5
4
4 8
5 5
7 8
6 5
0 0
*/