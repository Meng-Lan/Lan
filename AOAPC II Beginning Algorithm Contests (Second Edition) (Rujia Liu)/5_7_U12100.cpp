#include<iostream>
#include<cstdio>
#include<utility>
#include<queue>
using namespace std;
typedef pair<int, bool> P;
int main() {
	int T;
	cin >> T;
	while (T--) {
		queue<P> qp;
		int n, m, t;
		cin >> n >> m;
		int num[10] = { 0 };
		int maxx = 0;
		for (int i = 0; i < n; i++) {
			cin >> t;
			if (i == m)
				qp.push(make_pair(t, true));
			else
				qp.push(make_pair(t, false));
			if (t > maxx)
				maxx = t;
			num[t]++;
		}
		int cnt = 0;
		P temp = qp.front();
		//cout << temp.first<<"  "<<temp.second<<"  "<<maxx << endl;
		for (; !(temp.second)||temp.first!=maxx;) {
			if (temp.first == maxx) {
				num[maxx]--;
				if (num[maxx] == 0)
					for (; !num[maxx]; maxx--)
						;
				cnt++;
				qp.pop();
				temp = qp.front();
			}
			else {
				qp.push(make_pair(temp.first, temp.second));
				qp.pop();
				temp = qp.front();
			}
		}
		cnt++;
		cout << cnt << endl;
	}
	return 0;
}