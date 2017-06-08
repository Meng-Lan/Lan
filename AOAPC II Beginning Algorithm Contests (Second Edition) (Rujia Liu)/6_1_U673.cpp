#include<iostream>
#include<cstdio>
#include<stack>
#include<string>
#include<sstream>
//ע�↖�}��
//1���մ��Ϸ�
//2���Д�Y���r��Ҫ�Д����Ƿ񠑿�
using namespace std;
string s;
stack<char> sc;
int main() {
	int T;
	getline(cin, s);
	stringstream ss(s);
	ss >> T;
	while (T--) {
		getline(cin, s);
		while (!sc.empty())
			sc.pop();
		bool ok = true;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(' || s[i] == '[')
				sc.push(s[i]);
			else if (s[i] == ')' || s[i] == ']') {
				if (sc.empty()) {
					ok = false;
					break;
				}
				char c = sc.top();
				sc.pop();
				if (s[i] == ')'&&c != '(') {
					ok = false;
					break;
				}
				if (s[i] == ']'&&c != '[') {
					ok = false;
					break;
				}
			}
		}
		if (ok&&sc.empty()) {
			printf("Yes\n");
		}
		else
			printf("No\n");
	}
	return 0;
}