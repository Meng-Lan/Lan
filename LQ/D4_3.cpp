#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
/*��Ŀ���ѵ����ڶ�ȡ���֣�C++�ı�׼����һ����stringstream�������ַ������ж�ȡ�������ַ����������Զ�ȡ�����������
�������ҵ����Լ�д��ȡ�еĺ����ʹ��ַ����ж�ȡ�����ĺ�����ֻҪ�ѿո���ԣ��������ֿ�ʼ��ȡ�����������ո�ֹͣ�����棬�Ϳ�����
��Ϊ���ֲ��󣬰�������Ϊ�±꣬���׼��������߼оͿ����ҵ������������䣬���ҳ��յ����ֺ��ظ�������*/
int num[100005];
char str[10000];
int length;
void getline(char *);
void getint(char *);
int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		getline(str);
		getint(str);
		//printf("%s  %d\n", str,length);
	}
	int cnt;
	for (cnt = 0; !num[cnt]; cnt++)
		;
	int cnt2;
	for (cnt2 = 100000; !num[cnt2]; cnt2--)
		;
	int empty = 0,repeat = 0;
	//printf("cnt:%d cnt2:%d\n", cnt, cnt2);
	for (int i = cnt; i <= cnt2; i++)
		if (num[i] == 2)
			repeat = i;
		else if (!num[i])
			empty = i;
	printf("%d %d\n", empty, repeat);
	return 0;
}
void getline(char *str) {
	int i = 0;
	char c;
	for (; (c = getchar()) == '\n' || c == ' ';)
		;
	str[i++] = c;
	for (; (c = getchar()) != '\n'; i++) {
		str[i] = c;
	}
	str[i] = '\0';
	length = strlen(str);
}
void getint(char *str) {
	int i = 0;
	for (i = 0; i<length; ) {
		for (; (str[i]<'0'||str[i]>'9')&&i<length; i++)
			;
		if (i < length) {
			int temp = str[i++] - '0';
			for (; str[i] >= '0'&&str[i] <= '9'&&i<length; i++) {
				temp *= 10;
				temp += str[i] - '0';
			}
			num[temp]++;
			//printf("%d    ", temp);
		}
		//printf("%d** ", i);
	}
}