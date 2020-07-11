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
#define fi first
#define se second
#define pb push_back
#define is insert
#define mp std::make_pair
namespace IO {
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
	while(isdigit(c=IO::getchar())) { in*=10;in+=c-'0'; }
	in*=symbol;
}
inline int read() { static int x;read(x);return x; }
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

struct IN {
	int x,y,z,p;
	IN(int x,int y,int z,int p) :x(x),y(y),z(z),p(p) {}
	IN() :IN(0,0,0,0) {}
	void input() { scanf("%d%d%d%d",&x,&y,&z,&p); }
};
std::vector<IN> in;
struct Lan {
	int x,y;
	double dis;
	Lan(int x,int y,double dis) :x(x),y(y),dis(dis) {}
	Lan() :Lan(0,0,0.0) {}
	bool operator<(const Lan &rhs) { return dis<rhs.dis; }
};
std::vector<Lan> v;
const int maxn=1e3+10;
int n,cnt[maxn];

double sqr(double x) { return x*x; }
double distance(IN a,IN b) {
	return sqr(a.x-b.x)+sqr(a.y-b.y)+sqr(a.z-b.z);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#else
	freopen("hyper.in","r",stdin);
	freopen("hyper.out","w",stdout);
#endif // MengLan

	scanf("%d",&n);
	FOR(i,0,n) { IN t;t.input();in.pb(t); }
	FOR(i,0,n) FOR(j,i+1,n) v.pb({ i,j,distance(in[i],in[j]) });
	std::sort(v.begin(),v.end());
	for(auto &v:cnt) v=1;
	int i=0;
	std::pair<int,double> ans;
	while(i<v.size()) {
		int b=i;
		while(i<v.size()&&v[i].dis==v[b].dis) {
			if(in[v[i].x].p!=in[v[i].y].p) {
				--cnt[v[i].x];--cnt[v[i].y];
			}
			else {
				++cnt[v[i].x];++cnt[v[i].y];
			}
			++i;
		}
		int num=0;
		FOR(i,0,n) if(cnt[i]<0) ++num;
		if(num>ans.fi) ans=mp(num,v[b].dis);
	}
	printf("%d\n%.4f\n",ans.fi,sqrt(ans.se));

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
