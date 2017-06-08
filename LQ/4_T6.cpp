#include<cstdio>
#include<iostream>
using namespace std;
void sort3p(int* x, int len)
{
	int p = 0;
	int left = 0;
	int right = len - 1;

	while (p <= right) {
		if (x[p]<0) {
			int t = x[left];
			x[left] = x[p];
			x[p] = t;
			left++;
			p++;
		}
		else if (x[p]>0) {
			int t = x[right];
			x[right] = x[p];
			x[p] = t;
			right--;
		}
		else {
			int t = x[left];
			x[left] = x[p];
			x[p] = t;
			p++;
		}
	}

}
int main() {
	int num[20];
	for (int i = 0; i < 14; i++)
		cin >> num[i];
	sort3p(num, 14);
	for (int j = 0; j < 14; j++)
		cout << num[j] << " ";
	return 0;
}