#include<cstdio>
#include<iostream>
const int max = 10000000;
typedef long long ll;
ll num[max];
int n;
inline bool find(ll temp){
	int l = 0, r = n;
	while (r - l >= 1) {
		int i = (l + r) / 2;
		if (num[i] == temp)
			return true;
		else if (num[i] < temp)
			l = i + 1;
		else r = i;
	}
	return false;
}
int main() {
	for (ll i = 1; i < max; i++)
		num[i] = i*i;
	std::cin >> n;
	ll temp = (ll)n*(ll)n;
	int m = (int)sqrt((n / 2)*(n / 2)+ (n / 2)*(n / 2))+1;
	int ans = 0;
	//std::cout << n << "  " << m << "  " << temp << std::endl;
	for (int i = 1; i <= m; i++) 
		if (find(temp - num[i]))
			ans++;
	std::cout << ans << std::endl;
	return 0;
}