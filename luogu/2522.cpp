#include<iostream>
#include<string>
using namespace std;
int main() {
	string uim, xiao;
	int n;
	cin >> n >> xiao >> uim;
	int u = 0, x = 0;
	for (int i = 0; i < n; i++) {
		if (uim[i] == '<')
			u++;
		if (xiao[i] == '>')
			x++;
	}
	//cout << x << "  " << u << endl;
	if (x > u)
		cout << "xiaoA wins." << endl;
	else if (x < u)
		cout << "uim wins." << endl;
	else
		cout << "Drew." << endl;
	return 0;
}