#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int main() {
	int n;
	while (cin >> n&&n) {
		queue<int> que;
		for (int i = 1; i <= n; i++)
			que.push(i);
		cout << "Discarded cards:";
		for (int i = 0; i < n - 1; i++) {
			int temp = que.front();
			cout <<" "<< temp;
			if (i != n - 2)
				cout << ',';
			que.pop();
			temp = que.front();
			que.pop();
			que.push(temp);
		}
		cout << endl << "Remaining card:" <<" "<< que.front() << endl;
	}
	return 0;
}