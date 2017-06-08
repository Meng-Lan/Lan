#include<iostream>
#include<algorithm>
#include<map>
#include<cctype>
#include<vector>
#include<string>
using namespace std;
vector<string> word;
map<string, int> temp;
string reper(string &s) {
	string t = s;
	for (int i = 0; i < s.size(); i++)
		t[i] = tolower(s[i]);
	sort(t.begin(), t.end());
	return t;
}
int main() {
	string s;
	while (cin >> s) {
		if (s[0] == '#') break;
		word.push_back(s);
		string t = reper(s);
		if (!temp.count(t))
			temp[t] = 0;
		temp[t]++;
	}
	vector<string> ans;
	for (vector<string>::iterator it = word.begin(); it != word.end(); it++)
		if (temp[reper(*it)] == 1)
			ans.push_back(*it);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << endl;
	return 0;
}