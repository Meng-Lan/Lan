#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
char str[55][1005];
char ans[1005];
enum lan { A = 0, C = 1, G = 2, T = 3 };
int t[4];
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int m, n;
		scanf("%d%d", &m, &n);
		for (int i = 0; i < m; i++)
			scanf(" %s", str[i]);
		int SUM = 0;
		for (int i = 0; i < n; i++) {
			memset(t, 0, sizeof(t));
			for (int j = 0; j < m; j++) {
				if (str[j][i] == 'A') t[lan::A]++;
				else if (str[j][i] == 'T') t[lan::T]++;
				else if (str[j][i] == 'C') t[lan::C]++;
				else if (str[j][i] == 'G') t[lan::G]++;
			}
			int temp = 0, sum = 0;
			for (int j = 0; j < 4; j++) {
				if (t[j] > t[temp])
					temp = j;
				sum += t[j];
			}
			SUM += sum - t[temp];
			if (temp == 0) putchar('A');
			else if (temp == 1) putchar('C');
			else if (temp == 2) putchar('G');
			else if (temp == 3) putchar('T');
		}
		//ans[n] = '\0';
		printf("\n%d\n", SUM);
	}
	return 0;
}
/*
5 8
TATGATAC
TAAGCTAC
AAAGATCC
TGAGATAC
TAAGATGT
*/