#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<sstream>
using namespace std;
const int maxn = 1000 + 5;
int len[180];
int main() {
	vector<string> code[maxn];
	string temp;
	int n = 0, m = 0;
	for (n = 0; getline(cin, temp); n++) {
		stringstream ss(temp);
		while (ss >> temp)
			code[n].push_back(temp);
		if (code[n].size() > m)
			m = code[n].size();
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < code[i].size(); j++)
			if (code[i][j].size()>len[j])
				len[j] = code[i][j].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < code[i].size(); j++) {
			cout << code[i][j];
			if (j != code[i].size() - 1)
				for (int k = code[i][j].size(); k <= len[j]; k++)
					putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
/*
start:  integer;    // begins here
stop: integer; //  ends here
s:  string;
c:   char; // temp
*/