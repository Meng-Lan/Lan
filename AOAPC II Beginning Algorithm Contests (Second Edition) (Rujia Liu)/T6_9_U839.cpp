#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
bool solve(int &w) {
	int d1, w1, d2, w2;
	bool b1 = true, b2 = true;
	cin >> w1 >> d1 >> w2 >> d2;
	if (!w1) b1=solve(w1);
	if (!w2) b2=solve(w2);
	w = w1 + w2;
	return b2&&b1 && (w1*d1 == w2*d2);
}
int main() {
	int T, w;
	cin >> T;
	while (T--) {
		if (solve(w))
			printf("YES\n");
		else
			printf("NO\n");
		if (T)
			putchar('\n');
	}
	return 0;
}