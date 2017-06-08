#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int max = 1e6 + 5;
inline void swap(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp;
}
vector<int> lan[max];
int main(){
	int t;
	cin >> t;
	while(t--){
		int n, m;
		cin >> n >> m;
		int a1, b1, a2, b2, a3, b3;
		cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
		if (a1 > b1)
			swap(a1, b1);
		if (a2 > b2)
			swap(a2, b2);
		if (a3 > b3)
			swap(a3, b3);
		int s, t;
		long long ans = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &s, &t);
			lan[s].push_back(i);
			lan[t].push_back(i);
		}
		unsigned int t1 = ~0u, t2 = ~0u, t3 = ~0u, t4 = ~0u;
		for (int i = 1; i <= m;i++){
			