#include<iostream>
#include<cstdio>
#include<stack>
#include<string>
using namespace std;
struct Lan {
	int a, b;
	Lan(int a=0, int b=0) :a(a), b(b) {}
}m[26];
stack<Lan> s;
int main() {
	int n;
	cin >> n;
	string temp;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		int k = temp[0] - 'A';
		cin >> m[k].a >> m[k].b;
	}
	while (cin >> temp) {
		int len = temp.length();
		bool off = false;
		int ans = 0;
		for (int i = 0; i < len; i++) {
			if (isalpha(temp[i])) s.push(m[temp[i] - 'A']);
			else if (temp[i] == ')') {
				Lan t2 = s.top();
				s.pop();
				Lan t1 = s.top();
				s.pop();
				if (t1.b != t2.a) {
					off = true;
					break;
				}
				ans += t1.a*t1.b*t2.b;
				s.push(Lan(t1.a, t2.b));
			}
		}
		if (off)
			printf("error\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}