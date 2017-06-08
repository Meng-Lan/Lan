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
typedef pair<string, int> P;
#define mp make_pair

struct Lan {
	string name;
	int tot, tot1, the,sum;
	bool cadre, west;
	//Lan(int &tot, int &tot1, int &the, bool &cadre, bool &west,int sum=0) :tot(tot), tot1(tot1), the(the), cadre(cadre), west(west),sum(sum) {}
	//Lan() :tot(0), tot1(0), the(0), cadre(false), west(false),sum(0) {}
	bool operator < (const Lan &t) {
		return sum < t.sum;
	}
};
vector<Lan> students;
int main() {
	int n;
	scanf("%d", &n);
	Lan t;
	char s[10], s1[10];
	for (int i = 0; i < n; i++) {
		cin >> t.name;
		scanf("%d%d %s %s%d", &t.tot, &t.tot1, s, s1, &t.the);
		t.cadre = s[0] == 'Y' ? true : false;
		t.west = s1[0] == 'Y' ? true : false;
		t.sum = 0;
		students.push_back(t);
	}
	int tot = 0;
	P Max;
	Max.second = 0;
	for (vector<Lan>::iterator it = students.begin(); it != students.end(); it++) {
		if (it->tot > 80 && it->the) it->sum += 8000;
		if (it->tot>85 && it->tot1>80) it->sum += 4000;
		if (it->tot > 90) it->sum += 2000;
		if (it->tot > 85 && it->west) it->sum += 1000;
		if (it->tot1 > 80 && it->cadre) it->sum += 850;
		tot += it->sum;
		if (it->sum > Max.second) {
			Max.first = it->name;
			Max.second = it->sum;
		}
	}
	cout << Max.first << endl << Max.second << endl << tot << endl;
	//for (auto &p : students)
	//	cout << p.name << ' ' << p.tot << ' ' << p.tot1 << ' ' << p.the << ' ' << p.cadre << ' ' << p.west << ' ' << p.sum << endl;
	return 0;
}