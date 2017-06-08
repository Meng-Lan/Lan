#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<set>
std::set<int> s;
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	int tot = 0;
	for (int i = 0; i < 3; i++) {
		int a;
		cin >> a;
		tot += a;
		int temp;
		while (a--) {
			scanf("%d", &temp);
			s.insert(temp);
		}
	}
	for (std::set<int>::iterator it = s.begin(); it != s.end(); it++)
		cout << *it << " ";
	return 0;
}