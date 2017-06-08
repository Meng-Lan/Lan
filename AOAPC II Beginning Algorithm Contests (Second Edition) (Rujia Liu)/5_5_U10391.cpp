#include<iostream>
#include<cstdio>
#include<map>
#include<string>
#include<set>
using namespace std;
int main() {
	set<string> ss;
	string temp;
	while (cin >> temp)
		ss.insert(temp);
	set<string>::iterator it;
	for (it = ss.begin(); it != ss.end(); it++) {
		temp = *it;
		for (int i = 1; i < temp.size() - 1; i++)
			if (ss.count(temp.substr(0, i)) && ss.count(temp.substr(i))) {
				cout << temp << endl;
				break;
			}
	}
	return 0;
}