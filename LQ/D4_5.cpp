#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
/*����Խ����Խɵ���߶�����һ����50%���Ƶ���Ŀ��Ȼ��ȴ��������ʱд�Ĵ��롣
���������ͬ����ʵ�ǣ������ǵ�ÿһ����ײ�������������Կ����ǲ�����������Ѹ�ð��������һ���ˣ�
ֻҪ�жϵ�һֻ���ϻ����Щ���ϲ���������Ϳ��Եó��𰸣���Ȼ���������ײ��һֻ����֮��
����һֻ���ϻ���Ÿ�ð���������ͬ���򣩵Ĳ������*/
int abs(int n) {
	if (n >= 0)
		return n;
	else
		return -n;
}
int main() {
	int n;
	scanf("%d", &n);
	int *p = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
		scanf("%d", p + i);
	int sign = p[0] >= 0 ? 1 : -1;
	int ans = 1;
	int exp = 0;
	for (int i = 1; i < n; i++) {
		if (sign == 1) {
			if (p[i]<0 && abs(p[i])>p[0])
				ans++;
		}
		else {
			if (p[i] > 0 && p[i] < abs(p[0]))
				ans++;
		}
	}
	//printf("%d\n", ans);
	if (ans > 1)
		for (int i = 1; i < n; i++)
			if (sign == 1) {
				if (p[i] > 0 && p[i] < p[0])
					ans++;
			}
			else
				if (p[i]<0 && abs(p[i])>abs(p[0]))
					ans++;
	printf("%d\n", ans);
	return 0;;
}