#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<cstring>
char str[1024];
char stack[512];
void pop(void);
void push(char);
char top(void);
int p = 0;
int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", str);
		int length = strlen(str);
		char c;
		int sta = 1;
		for (int i = 0; i < length; i++) {
			if (str[i] == '(' || str[i] == '[')
				push(str[i]);
			else {
				if (p == 0) {
					printf("No\n");
					sta = 0;
					break;
				}
				c = top();
				pop();
				if (c == '(') {
					if (str[i] != ')') {
						printf("No\n");
						sta = 0;
						break;
					}
				}
				else if (str[i] != ']') {
					printf("No\n");
					sta = 0;
					break;
				}
			}
		}
		if (sta)
			if (p < 0)
				printf("No\n");
			else
				printf("Yes\n");
		p = 0;
	}
	return 0;
}
void pop() {
	p--;
}
void push(char c) {
	stack[p++] = c;
}
char top() {
	return stack[p-1];
}