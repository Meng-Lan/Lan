#include<iostream>
#include<cstdio>
#include<cstring>
char str[20][1000];
bool maxx(int m, int n) {
	int lenm = strlen(str[m]);
	int lenn = strlen(str[n]);
	if (lenm > lenn)
		return false;
	else if (lenm < lenn)
		return true;
	else {
		for (int i = 0; i < lenm; i++)
			if (str[m][i]>str[n][i])
				return false;
			else if (str[m][i] < str[n][i])
				return true;
	}
}
int main() {
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
		std::cin >> str[i];
	int max = 0;
	for (int i = 1; i < n; i++)
		if (maxx(max, i))
			max = i;
	std::cout << max + 1 << std::endl<<str[max]<<std::endl;
	return 0;
}