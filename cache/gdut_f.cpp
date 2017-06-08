#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int n, num[55];
long long ans = 0;
const int maxn = 1e9;
void bfs(int t, int k,int sum) {
	int  cnt = 0;
	for (int i = k; i < n; i++) {
		if (sum*num[i] <= maxn) {
			if (t & 1)
				ans -= maxn / (sum*num[i]);
			else
				ans += maxn / (sum*num[i]);
			cnt++;
		}
	}
	if (!cnt)
		return;
	for (int i = k; i < n; i++)
		for (int j = 0;
}
int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> num[i];
		ans = 1e9;
		bfs(1,0,1);