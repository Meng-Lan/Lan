#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
const int max = 1 << 10;
int num[max][4];
int main() {
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	while (cin >> n) {
		int temp = 5;
		for (int i = 0; i < n; i++) {
			scanf("%d.%d.%d.%d", num[i], num[i] + 1, num[i] + 2, num[i] + 3);
			if (temp)
				for (int j = 0; j < 4; j++)
					if (num[i][j] != num[0][j])
						if (j < temp)
							temp = j;
		}
		int max = 0, min = 1 << 8;
		for (int i = 0; i < n; i++) {
			if (num[i][temp]>max)
				max = num[i][temp];
			if (num[i][temp] < min)
				min = num[i][temp];
		}
		int t = 0;
		for (int i = 1; i <= 8; i++) {
			if (min % 2 != max % 2)
				t = i;
			min /= 2;
			max /= 2;
		}
		int ym = ((1 << 8) - 1)-((1 << t)-1);
		int ip = num[0][temp] & ym;
		for (int i = 0; i < 4; i++) {
			if (i < temp)
				cout << num[0][i];
			else if (i == temp)
				cout << ip;
			else if (i>temp)
				cout << 0;
			if (i != 3)
				cout << '.';
			else cout << endl;
		}
		for (int i = 0; i < 4; i++) {
			if (i < temp)
				cout <<(1<<8)-1;
			else if (i == temp)
				cout << ym;
			else if (i>temp)
				cout << 0;
			if (i != 3)
				cout << '.';
			else cout << endl;
		}
	}
	return 0;
}