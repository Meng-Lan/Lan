#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 5e5 + 10;
char s[maxn],cmd[maxn];
int t[maxn],Left[maxn],Right[maxn];
void line(int L, int R) {
	Right[L] = R;
	Left[R] = L;
}
int main() {
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 2; i <= n; i++) {
		Left[i] = i - 1;
		Right[i] = (i + 1) % (n+1);
	}
	Left[1] = n;
	Right[1] = 2;
	scanf(" %s", s + 1);
	scanf(" %s", cmd + 1);
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '(')
			cnt++;
		t[i] = cnt;
		if (s[i] == ')')
			cnt--;
	}
	//p -= 1;
	for (int i = 1; i <= m; i++) {
		if (cmd[i] == 'L') {
			if (Left[p] > p)
				;
			else
				p = Left[p];
		}
		else if (cmd[i] == 'R') {
			if (Right[p] < p)
				;
			else
				p = Right[p];
		}
		else {
			if (s[p] == '(') {
				int L_line = Left[p];
				int L = p;
				int lcnt = t[p];
				while (t[++p] != lcnt)
					;
				int R = p;
				int R_line = Right[p];
				line(L_line, R_line);
				for (int i = L; i <= R; i++)
					t[i] = 0;
				if (Right[p] < p)
					p = Left[p];
				else
					p = Right[p];
			}
			else if (s[p] == ')') {
				int R_line = Right[p];
				int R = p;
				int rcnt = t[p];
				while (t[--p] != rcnt)
					;
				int L = p;
				int L_line = Left[p];
				line(L_line, R_line);
				for (int i = L; i <= R; i++)
					t[i] = 0;
				if (Right[p] < p)
					p = Left[p];
				else
					p = Right[p];
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (t[i])
			printf("%c", s[i]);
	putchar('\n');
	return 0;
}