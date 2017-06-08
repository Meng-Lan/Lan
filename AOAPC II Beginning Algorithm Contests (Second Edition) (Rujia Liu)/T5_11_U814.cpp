#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<map>
using namespace std;
#define FOR(i, n) for (int i = 0; i < (n);i++)
void get_add(const string& temp, string& user, string& mta) {
	int mid = temp.find('@');
	user = temp.substr(0, mid);
	mta = temp.substr(mid + 1);
}
int main() {
	string temp, str, user1, user2, mta1, mta2;
	set<string> sstr;
	int n;
	while (cin >> temp&&temp != "*") {
		cin >> mta1 >> n;
		FOR(i, n) {
			cin >> temp;
			sstr.insert(temp + "@" + mta1);
		}
	}
	while (cin >> str&&str != "*") {
		get_add(str, user1, mta1);
		//cout << user1 << "  " << mta1 << endl;
		vector<string> mta;
		map<string, vector<string> > dest;
		set<string> vis;
		while (cin >> temp&&temp != "*") {
			get_add(temp, user2, mta2);
			if (vis.count(temp)) continue;
			vis.insert(temp);
			if (!dest.count(mta2)) {
				mta.push_back(mta2);
				dest[mta2] = vector<string>();
			}
			dest[mta2].push_back(temp);
		}
		getline(cin, temp);
		string data;
		while (getline(cin, temp) && temp[0] != '*')
			data += "     " + temp + "\n";
		FOR(i, mta.size()) {
			string mta2 = mta[i];
			vector<string> users = dest[mta2];
			cout << "Connection between " << mta1 << " and " << mta2 << endl;
			cout << "     HELO " << mta1 << endl;
			cout << "     250\n";
			cout << "     MAIL FROM:<" << str << ">\n";
			cout << "     250\n";
			bool ok = false;
			FOR(i, users.size()) {
				cout << "     RCPT TO:<" << users[i] << ">\n";
				if (sstr.count(users[i])) {
					ok = true;
					cout << "     250\n";
				}
				else cout << "     550\n";
			}
			if (ok) {
				cout << "     DATA\n     354\n";
				cout << data;
				cout << "     .\n";
				cout << "     250\n";
			}
			cout << "     QUIT\n     221\n";
		}
	}
	return 0;
}