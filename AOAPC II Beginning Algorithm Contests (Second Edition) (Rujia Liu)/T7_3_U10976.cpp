#include<iostream>
#include<cstdio>
#include<vector>
#include<utility>
using namespace std;
vector<pair<int,int> > ans;
int GCD(int a, int b) {
	return b>0 ? GCD(b, a%b) : a;
}
int main() {
	int k;
	while (scanf("%d", &k)==1) {
		ans.clear();
		for (int i = k + 1; i <= 2 * k; i++) {
			int x = i - k;
			int y = k*i;
			int gcd = GCD(x, y);
			x /= gcd;
			y /= gcd;
			if (x == 1)
				ans.push_back(make_pair(y, i));
		}
		cout << ans.size() << endl;
		for (auto &t : ans) {
			cout << "1/" << k << " = " << "1/" << t.first << " + 1/" << t.second << endl;
		}
	}
	return 0;
}