#include<iostream>
#include<cstdio>
#include<string>
#include<map>
#include<set>
#include<vector>
using namespace std;
struct Lan {
	string book, author;
	bool off;
};
bool operator <(const Lan& t1,const Lan&t2) {
	if (t1.author != t2.author)
		return t1.author < t2.author;
	else
		return t1.book < t2.book;
}
int main() {
	string s, t;
	map<string, Lan> mp;
	set<Lan> sl, now, brrow, rt;
	while (getline(cin, s)) {
		if (s == "END")
			break;
		int begin = s.find('"');
		int end = s.find('"', begin + 1);
		int by = s.find("by", end + 1);
		Lan temp;
		temp.book = s.substr(begin, end+1);
		temp.author = s.substr(by+2);
		sl.insert(temp);
		now.insert(temp);
		mp[temp.book] = temp;
	}
	for (;;) {
		cin >> s;
		if (s == "END")
			break;
		if (s == "SHELVE") {
			set<Lan>::iterator it;
			for (it = rt.begin(); it != rt.end(); it++) {
				now.insert(*it);
				set<Lan>::reverse_iterator reit;
				for (reit = now.rbegin(); reit != now.rend(); reit++) {
					if (reit->book == it->book&&reit->author == it->author)
						break;
				}
				Lan temp = *reit;
				if (++reit != now.rend()) {
					Lan temp2 = *reit;
					cout << "Put " << temp.book << " after " << temp2.book << endl;
				}
				else
					cout << "Put " << temp.book << " first\n";
			}
			rt.clear();
			cout << "END\n";
			continue;
		}
		if (s == "BORROW") {
			getline(cin, t);
			int begin = t.find('"');
			int end = t.find('"', begin + 1);
			t = t.substr(begin, end);
			if (now.count(mp[t])) {
				brrow.insert(mp[t]);
				now.erase(mp[t]);
			}
			else {
			}
			continue;
		}
		if (s == "RETURN") {
			getline(cin, t);
			int begin = t.find('"');
			int end = t.find('"', begin + 1);
			t = t.substr(begin, end);
			if (brrow.count(mp[t])) {
				brrow.erase(mp[t]);
				rt.insert(mp[t]);
			}
		}
	}
	return 0;
}