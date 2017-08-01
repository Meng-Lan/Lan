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

const int maxn=1e5+10;
struct Lan {
	ll a,b;
	Lan(ll a,ll b) :a(a),b(b) {}
	Lan() :Lan(0,1) {}
	Lan operator-(Lan rhs) const{
		ll g=gcd(b,rhs.b),l=b/g*rhs.b;
		ll t1=rhs.b/g*a,t2=b/g*rhs.a;
		ll t=t1-t2;g=gcd(t,l);
		return Lan(t/g,l/g);
	}
	Lan operator+(Lan rhs) const{
		ll g=gcd(b,rhs.b),l=b/g*rhs.b;
		ll t1=rhs.b/g*a,t2=b/g*rhs.a;
		ll t=t1+t2;g=gcd(t,l);
		return Lan(t/g,l/g);
	}
	Lan operator/(Lan rhs) const{
		std::swap(rhs.a,rhs.b);
		ll t1=a*rhs.a,t2=b*rhs.b;
		ll g=gcd(t1,t2);
		return Lan(t1/g,t2/g);
	}
	Lan operator*(Lan rhs)const {
		ll t1=a*rhs.a,t2=b*rhs.b;
		ll g=gcd(t1,t2);
		return Lan(t1/g,t2/g);
	}
	Lan operator=(const Lan &rhs) {
		a=rhs.a;b=rhs.b;
		return *this;
	}
	Lan operator+=(const Lan &rhs) {
		*this=*this+rhs;
		return *this;
	}
	bool operator<=(const Lan &rhs)const {
		return a*rhs.b<=b*rhs.a;
	}
	bool operator<(const Lan &rhs)const {
		return a*rhs.b<b*rhs.a;
	}
	void input() { scanf("%lld%lld",&a,&b); }
}in[maxn];
int n,c,t;

inline Lan getc2(const Lan &rhs,const Lan &m) {
	ll a=(m.a-rhs.a*m.b)*rhs.b,b=t*m.b-m.a;
	ll g=gcd(a,b);
	return Lan(a/g,b/g);
}

bool check(Lan m) {
	Lan need;
	FOR(i,0,n) {
		Lan t=getc2(in[i],m);
		//printf("t%d : (%lld/%lld)\n",i,t.a,t.b);
		need+=t;
	}
	//printf("need:(%lld/%lld)\n",need.a,need.b);
	return need<=Lan(c,1)&&Lan(0,1)<=need;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d%d",&n,&t,&c);
	int big=0,small=0;
	FOR(i,0,n) { in[i].input(); big+=(in[i].a<t);small+=(in[i].a>t); }
	//cout<<big<<' '<<small<<endl;
	if(big&&small) puts("Impossible");
	else if (big) {
		int min=1e9;
		FOR(i,0,n) min=std::min(min,(int)in[i].a);
		int len=log2((t-min)*1e3);
		Lan l(min,1),r(t,1);
		FOR(i,0,len){
			Lan m=(l+r)/Lan(2,1);
			if (check(m)) l=m;
			else r=m;
		}
		if(check(l)) { printf("Possible\n%.4f\n",(double)l.a/l.b); }
		else puts("Impossible");
	}
	else if (small) {
		int min=1e9;
		FOR(i,0,n) min=std::min(min,(int)in[i].a);
		if (check(Lan(min,1))) { printf("Possible\n%.4f\n",(double)min); }
		else puts("Impossible");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}