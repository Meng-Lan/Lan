#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
int num[200005];
int main() {
	int n, sta = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);
	int  p = 0;
	sta = num[0];
	for (int i = 1; i < n; i++) {
		if (sta >= 0)
			if (num[i] >= 0)
				num[p] += num[i];
			else {
				num[++p] = num[i];
				sta = num[i];
			}
		else {
			if (num[i] < 0)
				num[p] += num[i];
			else {
				num[++p] = num[i];
				sta = num[i];
			}
		}
	}
	sta = num[0];
	int count = p;
	for (;;){
		int cnt = 0;
		for (int i = 1; i <= count;i++){

	for (int i = 0; i <= p; i++)
		printf("%d ", num[i]);
	return 0;
}