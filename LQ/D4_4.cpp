#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
/*�����ĵ���Ŀ������һ�������Ʋ��֣�Ȼ�������ͼ��
��Ϊͼ��ֻ�����ַ��ϣ��Ϳ�����0��1�ֱ��ʾ�������ʱ����ƣ�
�����Ļ�����дһ������Ȼ����ճ���������µ�Ĳ���*/
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