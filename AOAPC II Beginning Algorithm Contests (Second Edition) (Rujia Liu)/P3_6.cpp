#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<cstring>
const int maxn = 105;
bool less(char* str, int p, int q) {
	int n = strlen(str);
	for (int i = 0; i < n; i++)
		if (str[(i + p) % n]<str[(i + q) % n])
			return false;
		else if (str[(i + p) % n] > str[(i + q) % n])
			return true;
	return false;
}
/*bool less(char* str, int p, int q) {
	int n = strlen(str);
	for (int i = 0; i < n; i++)
		if (str[(i + p) % n]!=str[(i + q) % n])
			return str[(i + p) % n] < str[(i + q) % n])
	return false;
}*/
int main() {
	int T;
	char str[maxn];
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str);
		int n = strlen(str);
		int ans = 0;
		for (int i = 1; i < n; i++)
			if (less(str, ans, i))
				ans = i;
		for (int i = 0; i < n; i++)
			putchar(str[(i + ans) % n]);
		putchar('\n');
	}
	return 0;
}
