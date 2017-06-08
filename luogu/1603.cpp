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
#define mp make_pair
string ts("one two three four five six seven eight nine ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen nineteen twenty");
map<string, int> ms;
vector<int> num;

bool cmp(const string &s, const string &t) {
	return s + t < t + s;
}

int main() {
	stringstream ss(ts);
	string s;
	for (int i = 1; ss >> s; i++)
		ms[s] = i;
	ms["a"] = 1; ms["both"] = 2; ms["another"] = 1; ms["first"] = 1;
	ms["second"] = 2; ms["third"] = 3;
	//for (auto &t : ms)
	//	cout << t.first << " " << t.second << endl;
	getline(cin, s);
	for (int i = 0; i < s.size(); i++)
		if (isalpha(s[i]))
			s[i] = tolower(s[i]);
	//cout << s << endl;
	stringstream ss1(s);
	int cnt = 0;
	while (ss1 >> s) {
		if (ms.find(s) != ms.end())
			num.push_back(ms[s]);
	}
	vector<string> vs;
	for (int i = 0; i < num.size(); i++) {
		s.clear();
		int t = (num[i] * num[i]) % 100;
		if (t >= 10) {
			s.push_back(t / 10);
			s.push_back(t % 10 );
		}
		else {
			s.push_back(0);
			s.push_back(t);
		}
		vs.push_back(s);
	}
	sort(vs.begin(), vs.end(), cmp);
	s.clear();
	for (int i = 0; i < vs.size(); i++)
		s += vs[i];
	bool begin = false;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != 0)
			begin = true;
		if (begin)
			printf("%d", s[i]);
	}
	if (!begin)
		putchar('0');
	putchar('\n');
	return 0;
}