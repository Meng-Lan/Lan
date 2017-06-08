#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int num[26];
int main() {
	int n;
	cin >> n;
	string temp;
	getline(cin, temp);
	while (n--) {
		memset(num, 0, sizeof(num));
		string s;
		getline(cin, s);
		int len = s.size();
		for (int i = 0; i < len; i++)
			if (s[i] >= 'a'&&s[i] <= 'z')
				num[s[i] - 'a']++;
		int cnt = 0;
		for (int i = 0; i < 26; i++)
			if (num[i])
				cnt++;
		cout << cnt << endl;
	}
	return 0;
}