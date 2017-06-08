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
	ll n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;
	ll x = n - max(abs(a + b - c - d),abs(a+c-b-d));
	if (x <= 0)
		cout << 0 << endl;
	else
		cout << x*n << endl;
	return 0;
}