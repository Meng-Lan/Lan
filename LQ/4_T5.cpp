#include<iostream>
#include<cstdio>
using namespace std;
char* prefix(char* haystack_start, char* needle_start)
{
	char* haystack = haystack_start;
	char* needle = needle_start;


	while (*haystack && *needle) {
		printf("%d %d\n", haystack, needle);
		if (haystack++&&needle++&&*haystack != *needle) return NULL;  //Ìî¿ÕÎ»ÖÃ
	}
	if (*needle) return NULL;

	return haystack_start;
}
char s1[100], s2[100];
int main() {
	cin >> s1 >> s2;
	//cout << s1 << s2;
	char *s3;
	prefix(s1, s2);
	return 0;
}