#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<cstdlib>
const int maxn = 105;
char s1[maxn], s2[maxn];
int n1[26], n2[26];
int cmp(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}
char stand(char c) {
	if (c >= 'A'&&c <= 'Z')
		return c - 'A' + 'a';
	else
		return c;
}
int main() {
	scanf("%s%s", s1, s2);
	int len1 = strlen(s1);
	for (int i = 0; i < len1; i++)
		n1[stand(s1[i]) - 'a']++;
	int len2 = strlen(s2);
	for (int i = 0; i < len2; i++)
		n2[stand(s2[i]) - 'a']++;
	qsort(n1, 26, sizeof(int), cmp);
	qsort(n2, 26, sizeof(int), cmp);/*
	for (int i = 0; i < 26; i++)
		printf("%d ", n1[i]);
	putchar('\n');
	for (int i = 0; i < 26; i++)
		printf("%d ", n2[i]);*/
	int off = 0;
	for (int i = 0; i < 26;i++)
		if (n1[i] != n2[i])
			off = 1;
	if (off)
		printf("No\n");
	else
		printf("Yes\n");
	return 0;
}