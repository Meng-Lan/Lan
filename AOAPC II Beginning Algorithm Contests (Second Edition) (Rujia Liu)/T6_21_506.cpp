#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<string>
#include<algorithm>
#include<map>
#include<sstream>
using namespace std;
const int maxn = 1e4;
vector<int> depend[maxn], depend2[maxn], installed;
map<string, int> id;
vector<string> idcache;
int status[maxn], cnt;

int ID(string s) {
	if (id.count(s)) return id[s];
	idcache.push_back(s);
	id[s] = idcache.size();
	return id[s];
}

void install(int item, bool toplevel) {
	if (!status[item]) {
		for (int i = 0; i < depend[item].size(); i++)
			install(depend[item][i], false);
		cout << "   Installing " << idcache[item - 1] << endl;
		status[item] = toplevel ? 1 : 2;
		installed.push_back(item);
	}
}

bool needed(int item) {
	for (int i = 0; i < depend2[item].size(); i++)
		if (status[depend2[item][i]]) return true;
	return false;
}

void remove(int item, bool toplevel) {
	if ((toplevel || status[item] == 2) && !needed(item)) {
		status[item] = 0;
		installed.erase(remove(installed.begin(), installed.end(), item), installed.end());
		cout << "   Removing " << idcache[item - 1] << endl;
		for (int i = 0; i < depend[item].size(); i++)
			remove(depend[item][i], false);
	}
}

int main() {
	string s, op;
	while (getline(cin, s)) {
		cout << s << endl;
		stringstream ss(s);
		ss >> op;
		if (op[0] == 'E')
			break;
		if (op[0] == 'D') {
			string x, y;
			ss >> x;
			int idx = ID(x);
			while (ss >> y) {
				int idy = ID(y);
				depend[idx].push_back(idy);
				depend2[idy].push_back(idx);
			}
		}
		else if (op[0] == 'I') {
			string name;
			ss >> name;
			int id_name = ID(name);
			if (status[id_name])
				cout << "   " << idcache[id_name - 1] << " is already installed.\n";
			else
				install(id_name, true);
		}
		else if (op[0] == 'R') {
			string name;
			ss >> name;
			int id_name = ID(name);
			if (needed(id_name))
				cout << "   " << idcache[id_name - 1] << " is still needed.\n";
			else if (status[id_name] == 0)
				cout << "   " << idcache[id_name - 1] << " is not installed.\n";
			else
				remove(id_name, true);
		}
		else if (op[0] == 'L') {
			for (int i = 0; i < installed.size(); i++)
				cout << "   " << idcache[installed[i] - 1] << endl;
		}
	}
	return 0;
}