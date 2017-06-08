#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef pair<string, string> ps;
#define mp make_pair
#define pb push_back

string s1, s2;
map<string, string> m1, m2;

inline void action(string &s) {
	for (auto &t : s)
		if (!isalpha(t) && !isalnum(t))
			t = ' ';
}

inline void get_key_val(stringstream &ss, map<string, string> &ms) {
	string k, v;
	while (ss >> k) {
		ss >> v;
		ms[k] = v;
	}
}

inline void print(const vector<string> &vs, char ch) {
	putchar(ch);
	for (int i = 0; i < vs.size(); ++i) {
		if (i) putchar(',');
		cout << vs[i];
	}
	putchar('\n');
}

int main() {
	int T;
	scanf("%d ", &T);
	while (T--) {
		m1.clear(); m2.clear();
		getline(cin, s1); getline(cin, s2);
		action(s1); action(s2);
		stringstream ss1(s1), ss2(s2);
		get_key_val(ss1, m1);
		get_key_val(ss2, m2);
		vector<string> add, sub, change;
		for (auto &t : m1) {
			auto it = m2.find(t.first);
			if (it == m2.end())
				sub.push_back(t.first);
			else if (it->second != t.second)
				change.push_back(t.first);
		}
		for (auto &t : m2) {
			if (m1.find(t.first) == m1.end())
				add.push_back(t.first);
		}
		if (add.size())	print(add, '+');
		if (sub.size())	print(sub, '-');
		if (change.size()) print(change, '*');
		if (!add.size() && !sub.size() && !change.size()) puts("No changes");
		putchar('\n');
	}
	return 0;
}