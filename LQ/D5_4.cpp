#include<iostream>
#include<cstring>
int num[10];
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	int n;
	cin >> n;
	int temp;
	int ans = 0;
	for (int i = 1; i < n; i++) 
		for (int j = 1; j < 10000; j++) {
			memset(num, 0, sizeof(num));
			int off = 0;
			temp = i;
			for (; temp;) {
				if (!num[temp % 10])
					num[temp % 10] = 1;
				else {
					off = 1;
					break;
				}
				temp /= 10;
			}
			if (off)
				continue;
			temp = j;
			for (; temp;) {
				if (!num[temp % 10])
					num[temp % 10] = 1;
				else {
					off = 1;
					break;
				}
				temp /= 10;
			}
			if (off)
				continue;
			temp = (n - i)*j;
			for (; temp;) {
				if (!num[temp % 10])
					num[temp % 10] = 1;
				else {
					off = 1;
					break;
				}
				temp /= 10;
			}
			if (off)
				continue;
			for (int i = 1; i < 10;i++)
				if(!num[i])
					off = 1;
			if (num[0])
				off = 1;
			if (off)
				continue;
			ans++;
			printf("100=%d+%d/%d\n", i, (n - i)*j, j);
			break;
		}
	printf("%d\n", ans);
	return 0;
}