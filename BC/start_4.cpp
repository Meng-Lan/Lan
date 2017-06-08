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
map<string,int> ms;
int main() {
	string s;
	int n;
	cin >> n;
	while (n--) {
		cin >> s;
		sort(s.begin(), s.end());
		ms[s]++;
		cout << ms[s] - 1 << endl;
	}
	return 0;
}