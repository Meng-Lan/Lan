#include<iostream>
#include<set>
#include<utility>
#include<cstdio>
#include<map>
using namespace std;
typedef pair<int, int> P;
int main() {
	int n;
	while (cin >> n&&n) {
		map<P, int> mp;
		int x, y;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &x, &y);
			P temp = make_pair(y, x);
			if (mp.count(temp))
				if (mp[temp]>0) {
					mp[temp]--;
					continue;
				}
				else
					mp.erase(temp);
			temp = make_pair(x, y);
			if (!mp.count(temp)) {
				mp[temp] = 1;
				continue;
			}
			mp[temp]++;
		}
		map<P, int>::iterator it;
		bool off = true;
		pair<P, int> temp;
		for (it = mp.begin(); it != mp.end(); it++) {
			temp = *it;
			if (temp.second > 0)
				off = false;
		}
		if (off)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}