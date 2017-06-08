#include<iostream>
#include<cstring>
int num[1248];
void copy(char *, char *);
int main() {
	int n;
	char temp[15], str[100][15];
	using std::cin;
	using std::cout;
	using std::endl;
	int length;
	int cnt = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		length = strlen(temp);
		int sum = 0;
		for (int j = 0; j < length; j++) {
			if (temp[j] >= '0'&& temp[j] <= '9')
				sum += temp[j] - '0' + j * 62;
			else if (temp[j] >= 'a'&&temp[j] <= 'z')
				sum += temp[j] - 'a' + 10 + j * 62;
			else
				sum += temp[j] - 'A' + 36 + j * 62;
		}
		if (!num[sum]) {
			copy(str[cnt++], temp);
			num[sum]++;
		}
		else
			num[sum]++;
	}
	for (int i = 0; i < cnt; i++) {
		copy(temp, str[i]);
		int sum = 0;
		length = strlen(temp);
		for (int j = 0; j < length; j++) {
			if (temp[j] >= '0'&& temp[j] <= '9')
				sum += temp[j] - '0' + j * 62;
			else if (temp[j] >= 'a'&&temp[j] <= 'z')
				sum += temp[j] - 'a' + 10 + j * 62;
			else
				sum += temp[j] - 'A' + 36 + j * 62;
		}
		if (num[sum] % 2 == 1) {
			printf("%s\n", temp);
			break;
		}
	}
	return 0;
}
void copy(char *a, char *b) {
	int length = strlen(b);
	for (int i = 0; i <= length; i++)
		a[i] = b[i];
}