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
/*namespace IO {
inline char getchar() {
static const int BUFSIZE=5201314;
static char buf[BUFSIZE],*begin,*end;
if(begin==end) {
begin=buf;
end=buf+fread(buf,1,BUFSIZE,stdin);
if(begin==end) return -1;
}
return *begin++;
}
}
inline void read(int &in) {
int c,symbol=1;
while(isspace(c=IO::getchar()));
if(c=='-') { in=0;symbol=-1; }
else in=c-'0';
while(isalnum(c=IO::getchar())) { in*=10;in+=c-'0'; }
in*=symbol;
}
inline int read() { static int x;read(x);return x; }*/
ll Factorial(ll i) { return i > 1?i*Factorial(i-1):1; }
ll Combination(ll n,ll r) {
	if(n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for(ll i=n-r+1; i<=n; ++i) ansn*=i;
	for(ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if(!vis[i]) for(int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if(!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if(!phi[i])
		for(int j=i; j<=n; j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int maxn=505;
struct BMP {
	int left[maxn];
	bool T[maxn];
	int G[maxn][maxn];
	int n,m;

	void init(int n,int m) {
		this->n=n;
		this->m=m;
		memset(G,0,sizeof(G));
	}

	bool match(int u) {
		FOR(v,0,m) if(G[u][v]&&!T[v]) {
			T[v]=true;
			if(left[v]==-1||match(left[v])) {
				left[v]=u;
				return true;
			}
		}
		return false;
	}

	int solve() {
		memset(left,-1,sizeof(left));
		int ans=0;
		FOR(u,0,n) {
			memset(T,0,sizeof(T));
			if(match(u)) ++ans;
		}
		return ans;
	}
}solver;


struct Student {
	int h;
	std::string music,PE;
	Student(int h,std::string music,std::string PE) :h(h),music(music),PE(PE) {}
	Student()=default;
};

bool conflict(Student &l,Student &r) {
	return std::abs(l.h-r.h)<=40&&l.music==r.music&&l.PE!=r.PE;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		std::vector<Student> male,female;
		int n;scanf("%d",&n);
		FOR(i,0,n) {
			int h;
			std::string sex,music,PE;
			cin>>h>>sex>>music>>PE;
			if(sex=="M") male.push_back({ h,music,PE });
			else female.push_back({ h,music,PE });
		}
		int x=male.size(),y=female.size();
		solver.init(x,y);
		FOR(i,0,x) FOR(j,0,y) if(conflict(male[i],female[j])) solver.G[i][j]=1;
		printf("%d\n",x+y-solver.solve());
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}