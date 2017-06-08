#include<iostream>
#include<cstring>
int num[1024];
int main() {
	char str[1024];
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> str;
	int length = strlen(str);
	int sum = 0, temp;
	for (int i = 0; i < length; i++) {
		sum = 0;
		temp = 0;
		if (str[i] >= 'A'&&str[i] <= 'Z') {
			int j;
			for (j = 0; j ? str[i + j] >= 'a'&&str[i + j] <= 'z' : str[i + j] >= 'A'&&str[i + j] <= 'Z'; j++) {
				if (j == 0) {
					if (str[i + j] >= 'A'&&str[i + j] <= 'Z')
						temp += str[i + j] - 'A';
				}
				else
					if (str[i + j] >= 'a'&&str[i + j] <= 'z')
						temp += str[i + j] - 'a' + j * j * 52;
			}
			i += j;
			if (!num[temp])
				num[temp]++;
		}
	}
	int ans = 0;
	for (int i = 0; i < 1024; i++)
		if (num[i])
			ans++;
	printf("%d\n", ans);
	return 0;
}