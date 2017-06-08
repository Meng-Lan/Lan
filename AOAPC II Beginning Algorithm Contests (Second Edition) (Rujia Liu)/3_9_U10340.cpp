#include<iostream>
#include<cstdio>
#include<cstring>
const int maxn = 1000;
char s[maxn], t[maxn];
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> s >> t;
	int lens = strlen(s);
	int lent = strlen(t);
	int count = 0;
	for (int i = 0; i < lens; i++)
		if (s[i] == t[count])
			count++;
	if (count == lent)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}