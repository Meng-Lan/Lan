#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define mp make_pair
#define pb push_back
const int maxn = 1e6 + 10;
int num[maxn];
ll sum[maxn];

int main() {
	int n, k, h;
	scanf("%d%d%d", &n, &h, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", num + i);
		//i == 0 ? sum[i] = num[i] : sum[i] = sum[i - 1] + num[i];
	}
	ll op = 0, now = 0, next = 0;
	for (int i = 0; i < n;) {
		while (i < n&&now + num[i] <= h) now += num[i++];
		while (i < n && now + num[i] - h <= k) next += num[i++];
		next%k ? op += next / k + 1 : op += next / k;
		cout << now << " " << next << endl;
		now -= next;
	}
	printf("%lld\n", op);
	return 0;
}