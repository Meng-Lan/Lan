#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
vector<string> vs;
string s;
int main() {
	while (getline(cin,s)) {
		vs.push_back(s);
		cout << s << endl;
	}
	for (int i = vs.size() - 1; i >= 0;i--) {
		for (int j = vs[i].size(); j >= 0; j--)
			printf("%c", vs[i][j]);
		putchar('\n');
	}
	return 0;
}