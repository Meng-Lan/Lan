#include<iostream>
#include<string>
#include<vector>
using namespace std;
vector<string> vs[26];
int main() {
	string temp;
	while (getline(cin,temp)) {
		if (temp.size()==0)
			break;
		else
			vs[temp[0]-'a'].push_back(temp);
	}
	while (cin >> temp) {
		int ans = 0;
		int size = temp.size();
		for (int i = 0; i < vs[temp[0]-'a'].size(); i++) {
			int off = 0;
			for (int k = 0; k < size; k++)
				if (temp[k] != vs[temp[0]-'a'][i][k]) {
					off = 1;
					break;
				}
			if (off)
				continue;
			else
				ans++;
		}
		cout << ans << endl;
	}
	return 0;
}