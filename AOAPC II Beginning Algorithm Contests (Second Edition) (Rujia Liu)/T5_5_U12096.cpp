#include<iostream>
#include<stack>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<algorithm>
#include<iterator>
using namespace std;
typedef set<int> Set;
map<Set, int> idcache;
vector<Set> setcache;
int id(Set x) {
	if (idcache.count(x))
		return idcache[x];
	setcache.push_back(x);
	return idcache[x] = setcache.size() - 1;
}
#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())
int main() {
	int t;
	cin >> t;
	while (t--) {
		stack<int> s;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			string op;
			cin >> op;
			if (op[0] == 'P')
				s.push(id(Set()));
			else if (op[0] == 'D')
				s.push(s.top());
			else {
				Set x1 = setcache[s.top()];
				s.pop();
				Set x2 = setcache[s.top()];
				s.pop();
				Set x;
				if (op[0] == 'U')
					set_union(ALL(x1), ALL(x2), INS(x));
				if (op[0] == 'I')
					set_intersection(ALL(x1), ALL(x2), INS(x));
				if (op[0] == 'A') {
					x = x2;
					x.insert(id(x1));
				}
				s.push(id(x));
			}
			cout << setcache[s.top()].size() << endl;
		}
		cout << "***\n";
	}
	return 0;
}