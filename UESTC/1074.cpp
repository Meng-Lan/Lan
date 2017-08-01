#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int,int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1?i*Factorial(i-1):1; }
ll Combination(ll n,ll r) {
	if (n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for (ll i=n-r+1; i<=n; ++i) ansn*=i;
	for (ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if (!vis[i]) for (int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if (!phi[i])
		for (int j=i; j<=n; j+=i) {
			if (!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int maxn=1e6+10;
char s[maxn];
int n;

inline ll getll(char *&p) {
	ll num=0;
	while (isdigit(*p)) { num*=10;num+=*p++-'0'; }
	return num;
}

inline char getop(char *&p) { return *p++; }

inline int getpriority(char c) { return c=='+'||c=='-'?1:2; }

ll cal(ll num1,char op,ll num2) {
	switch (op) {
	case '+':return num1+num2;
	case '-':return num1-num2;
	case '*':return num1*num2;
	case '/':return num1/num2;
	default:
		break;
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d",&n);
	FOR(i,0,n) {
		scanf(" %s",s);
		char *p=s;
		std::stack<ll> num;
		std::stack<char> op;
		num.push(getll(p));
		while ((*p)!='\0') {
			if (op.empty()) { op.push(getop(p));num.push(getll(p)); continue;}
			char op1=op.top(),op2=getop(p);
			if (getpriority(op1)<getpriority(op2)) {
				op.push(op2);num.push(getll(p));
			}
			else {
				while (!op.empty()&&getpriority(op.top())>=getpriority(op2)) {
					ll num1=num.top();num.pop();
					ll num2=num.top();num.pop();
					num.push(cal(num2,op.top(),num1));
					op.pop();
				}
				op.push(op2);num.push(getll(p));
			}
		}
		while (!op.empty()) {
			ll num1=num.top();num.pop();
			ll num2=num.top();num.pop();
			num.push(cal(num2,op.top(),num1));
			op.pop();
		}
		cout<<num.top()<<endl;
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}