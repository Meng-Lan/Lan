#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
/*  字符串处理问题，先读入字符串，往后移动字符，将年份的位置空出来，填补年份，进行验证计算，填写验证码，输出*/
int num[] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
char *str = "10x98765432";
int main() {
	char temp[20];
	scanf("%s", temp);
	int i;
	for (i = 16; i > 7; i--)
		temp[i] = temp[i - 2];
	temp[6] = '1';
	temp[7] = '9';
	int sum = 0;
	for (int i = 0; i < 17; i++)
		sum += (temp[i] - '0')*num[i];
	temp[17] = str[sum % 11];
	for (int i = 0; i < 18; i++)
		printf("%c", temp[i]);
	printf("\n");
	return 0;
}