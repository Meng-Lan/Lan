#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
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
int main() {
	int a, b, c;
	cin >> a >> b >> c;
	if (c == 0)
		if (a == b)
			cout << "YES\n";
		else
			cout << "NO\n";
	else {
		if ((b - a) % c == 0 && (b - a) / c >= 0)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}