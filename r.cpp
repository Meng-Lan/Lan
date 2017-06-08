#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
typedef long long ll;
#define rd rand()/RAND_MAX 
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
const int maxn = 5e3;
const auto t = RAND_MAX >> 1;
int sign() {
	if (rand() >= t) return 1;
	else return -1;
}

int main() {
	srand(time(NULL));
	FOR(i, 0, 100) rd;
	int n = 100 * rd + 1, m = 100 * rd + 1;
	while (m > n) m = 100 * rd + 1;
	printf("%d %d\n", n, m);
	For(i, 1, n) printf("%d%c", 1000 * rd + 1, i == n ? '\n' : ' ');

	return 0;
}