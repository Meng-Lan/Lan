#include<iostream>
#include<cstdio>
int main() {
	int c, cnt = 1;
	while ((c = getchar()) != EOF) {
		if (c == '"')
			if (cnt) {
				cnt = 0;
				putchar('`');
				putchar('`');
			}
			else {
				cnt = 1;
				putchar('\'');
				putchar('\'');
			}
		else
			putchar(c);
	}
	return 0;
}