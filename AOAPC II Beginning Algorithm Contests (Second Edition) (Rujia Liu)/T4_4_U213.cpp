#include<cstdio>
#include<cstring>
int code[8][1 << 8];
char readchar() {
	int c;
	for (; (c = getchar()) != '\n'&&c != '\r';)
		return c;
}
int readint(int n) {
	int temp = 0;
	while(n--)
		temp = temp * 2 + readchar() - '0';
	return temp;
}
int readcode() {
	memset(code, 0, sizeof(code));
	int ch;
	ch = code[1][0] = readchar();
	for (int len = 2; len < 7; len++)
		for (int i = 0; i < (1 << len) - 1; i++) {
			ch = getchar();
			if (ch == EOF)
				return 0;
			if (ch == '\n' || ch == '\r')
				return 1;
			code[len][i] = ch;
		}
	return 1;
}
int main() {
	while (readcode()) {
		for (;;) {
			int len = readint(3);
			if (len == 0)
				break;
			for (;;) {
				int v = readint(len);
				if (v == (1 << len) - 1)
					break;
				putchar(code[len][v]);
			}
		}
		putchar('\n');
	}
	return 0;
}