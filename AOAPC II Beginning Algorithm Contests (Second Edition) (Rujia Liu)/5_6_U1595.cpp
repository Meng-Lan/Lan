#include<iostream>
#include<set>
#include<utility>
#include<cstdio>
using namespace std;
typedef pair<int, int> P;
const int maxn = 10005;
int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		set<P> sp;
		int x, y;
		int left = maxn, right = -maxn;
		int lefth = maxn, righth = -maxn;
		while (n--) {
			scanf("%d%d", &x, &y);
			P temp = make_pair(x, y);
			if (x < left)
				left = x;
			if (x > right)
				right = x;
			if (y < lefth)
				lefth = y;
			if (y > righth)
				righth = y;
			sp.insert(temp);
		}
		/*set<P>::iterator it;
		for (it = sp.begin(); it != sp.end(); it++) {
			P temp = *it;
			cout << temp.first << "  " << temp.second << endl;
		}*/
		//cout << left << "  " << right << endl;
		if ((left + right) & 1) {
			int mid1 = (left + right) / 2;
			int mid2 = mid1 + 1;
			bool off = true;
			for (int i = -lefth; i < righth; i++) {
				if (sp.count(make_pair(mid1, i))) {
					if (!sp.count(make_pair(mid2, i))) {
						off = false;
						break;
					}
					else {
						sp.erase(make_pair(mid1, i));
						sp.erase(make_pair(mid2, i));
					}
				}
			}
			if (!off) {
				cout << "NO\n";
				continue;
			}
			set<P>::iterator it;
			P temp;
			for (it = sp.begin(); it != sp.end(); it++) {
				temp = *it;
				if (temp.first < mid1) {
					if (!sp.count(make_pair(mid2 + mid1 - temp.first, temp.second))) {
						off = false;
						break;
					}
				}
				else {
					if (!sp.count(make_pair(mid1 - temp.first + mid2, temp.second))) {
						off = false;
						break;
					}
				}
			}
			if (!off) {
				cout << "NO\n";
				continue;
			}
			else {
				cout << "YES\n";
				continue;
			}
		}
		else {
			int mid = (left + right) / 2;
			bool off = true;
			for (int i = lefth; i < righth; i++)
				if (sp.count(make_pair(mid, i))) {
					sp.erase(make_pair(mid, i));
				}
			set<P>::iterator it;
			P temp;
			for (it = sp.begin(); it != sp.end();it++) {
				temp = *it;
				if (temp.first < mid) {
					if (!sp.count(make_pair(mid - temp.first + mid, temp.second))) {
						off = false;
						break;
					}
				}
				else
					if (!sp.count(make_pair(2 * mid - temp.first, temp.second))) {
						off = false;
						break;
					}
			}
			if (!off) {
				cout << "NO\n";
				continue;
			}
			else {
				cout << "YES\n";
				continue;
			}
		}
	}
	return 0;
}
