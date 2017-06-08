#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void f(int, int, int);
void t(int, int, int);
int a[10];
int main(){
	int n;
	scanf("%d", &n);
	f(n, 0, 0);
	return 0;
}
void f(int n, int d, int kase) {
	if (n >> 1 > 0)
		f(n >> 1, d + 1, n >> 1 & 1 ? kase + 1 : kase);
	if (n & 1) {
		/*printf("2");
		if (d != 1)
			printf("(");
		if (d == 0 || d == 2)
			printf("%d", d);*/
		if (d >= 3)
			t(d, 0, 0);
	/*	if (d != 1)
			printf(")");
		if (kase)
			printf("+");*/
	}
	//printf("n:%d d:%d kase:%d n&1:%d\n", n, d, kase,n&1);
}
void t(int n, int d, int kase) {
	if (n >> 1 > 0) {
		if (n >> 1 & 1) {
			if (a[kase] > 2)
				;
			else
				a[kase]++;
		}
		t(n >> 1, d + 1, kase);
	}
	if (n & 1) {
		printf("2");
		if (d != 1)
			printf("(");
		if (d == 0 || d == 2)
			printf("%d", d);
		if (d >= 3) {
			a[kase]--;
			t(d, 0, kase + 1);
		}
		if (d != 1)
			printf(")");
		if (kase)
			printf("+");
	}
	//printf("n:%d d:%d kase:%d n&1:%d\n", n, d, kase, n & 1);
}
