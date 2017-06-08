#include<iostream>
#include<cstdio>
#include<stack>
#include<string>
#include<sstream>
//注意問題：
//1：空串合法
//2：判斷結果時候，要判斷棧是否爲空
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