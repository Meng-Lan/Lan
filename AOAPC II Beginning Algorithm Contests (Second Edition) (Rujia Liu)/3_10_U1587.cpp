#include<cstdio>
#include<cstring>
#include<iostream>
#include<utility>
#include<algorithm>
typedef std::pair<int, int> P;
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	P p[6];
	int a, b;
	for (int i = 0; i < 6; i++) {
		cin >> a >> b;
		if (a > b) {
			p[i].first = a;
			p[i].second = b;
		}
		else {
			p[i].first = b; 
			p[i].second = a;
		}
	}
	int off = 0;
	std::sort(p, p + 6);
	for (int i = 0; i < 6; i += 2)
		if (p[i].first != p[i+1].first || p[i].second != p[i+1].second) {
			off = 1;
			break;
		}
	if(!off){
		if (p[0].first == p[2].first) {
			if (p[0].second == p[4].first&&p[2].second == p[4].second)
				;
			else if (p[0].second == p[4].second&&p[2].second == p[4].first)
				;
			else
				off = 1;
		}
		else if (p[0].first == p[2].second) {
			if (p[0].second == p[4].first&&p[2].first == p[4].second)
				;
			else if (p[0].second == p[4].second&&p[2].first == p[4].first)
				;
			else
				off = 1;
		}
		else
			off = 1;
		}
	if (off)
		cout << "No" << endl;
	else
		cout << "Yes" << endl;
	return 0;
}