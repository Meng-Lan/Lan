#include<iostream>
using namespace std;
int main() {
	int temp[10] = { 0 };
	int cnt = 0;
	for (int i = 12; i < 99; i++)
		for (int j = 123; j < 999; j++)
			if (i*j == (i / 10 * 100 + (j / 10) % 10 * 10 + i % 10)*((j / 100) * 10 + j % 10)){
				memset(temp, 0, sizeof(temp));
				temp[i / 10]++;
				temp[i % 10]++;
				temp[j / 100]++;
				temp[j % 10]++;
				temp[(j / 10) % 10]++;
				if (temp[0])
					continue;
				int off = 0;
				for (int i = 1; i < 10; i++)
					if (temp[i]>1)
						off = 1;
				if (off)
					continue;
				cnt++;
				cout << i << "*" << j << "=" << (i / 10 * 100 + (j / 10) % 10 * 10 + i % 10) << "*" << ((j / 100) * 10 + j % 10) << "=" << i*j << endl;
			}
	cout << cnt << endl;
	return 0;
}