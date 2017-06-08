#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
/*长得越大变得越傻，高二做过一道有50%类似的题目，然而却看不懂当时写的代码。
和那题的相同点其实是：蚂蚁们的每一次碰撞就立即反身，可以看成是擦肩而过，并把感冒传给和另一个人，
只要判断第一只蚂蚁会和哪些蚂蚁擦身而过，就可以得出答案，当然，如果蚂蚁撞上一只蚂蚁之后，
另外一只蚂蚁会带着感冒和蚂蚁身后（同方向）的擦身而过*/
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