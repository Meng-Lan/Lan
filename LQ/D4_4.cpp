#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
/*很无聊的题目，就是一个找相似部分，然后分区域画图；
因为图案只有两种符合，就可以用0，1分别表示，输出的时候控制，
其他的基本是写一两条，然后复制粘贴，更改下点的参数*/
int num[80][80];
int main() {
	int n;
	scanf("%d", &n);
	int mid = n * 2 + 3-1;
	num[mid][mid] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < 1 + i * 2; j++) {
			num[mid - 2 - i * 2][mid+j] = 1;
			num[mid + 2 + i * 2][mid+j] = 1;
			num[mid+j][mid - 2 - i * 2] = 1;
			num[mid+j][mid + 2 + i * 2] = 1;
			num[mid - 2 - i * 2][mid - j] = 1;
			num[mid + 2 + i * 2][mid - j] = 1;
			num[mid - j][mid - 2 - i * 2] = 1;
			num[mid - j][mid + 2 + i * 2] = 1;
		}
		num[mid - 1 - i * 2][mid + i * 2] = 1;
		num[mid + 1 + i * 2][mid + i * 2] = 1;
		num[mid + i * 2][mid - 1 - i * 2] = 1;
		num[mid + i * 2][mid + 1 + i * 2] = 1;
		num[mid - 1 - i * 2][mid - i * 2] = 1;
		num[mid + 1 + i * 2][mid - i * 2] = 1;
		num[mid - i * 2][mid - 1 - i * 2] = 1;
		num[mid - i * 2][mid + 1 + i * 2] = 1;
		num[mid  - i * 2][mid + i * 2] = 1;
		num[mid  + i * 2][mid + i * 2] = 1;
		num[mid  - i * 2][mid - i * 2] = 1;
		num[mid  + i * 2][mid - i * 2] = 1;
	}
	int max = n*4+6-1;
	for (int i = 0; i < max; i++) {
		for (int j = 0; j < max; j++)
			printf("%c", num[i][j] ? '$' : '.');
		printf("\n");
	}
	return 0;
}