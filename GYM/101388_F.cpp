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

struct Lan {
	int x,y,x2,y2;
	bool use;
	Lan(int x,int  y,int x2,int y2,bool use) :x(x),y(y),x2(x2),y2(y2),use(use) {}
	Lan() :Lan(0,0,0,0,false) {}
	int area() { return (x2-x)*(y2-y); }
	bool insied(int x1,int y1) { return x<=x1&&y<=y1&&x1<=x2&&y1<=y2; }
	bool touch(Lan b) {
		return insied(b.x,b.y)||insied(b.x,b.y2)||insied(b.x2,b.y)||insied(b.x2,b.y2);
	}
	void expand(Lan b) {
		x=std::min(x,b.x);y=std::min(y,b.y);
		x2=std::max(x2,b.x2);y2=std::max(y2,b.y2);
	}
};
std::vector<Lan> in;
int x,y,n;

bool check(int i) {
	for(auto it=in.begin()+i+1;it!=in.end();++it) {
		if(in[i].touch(*it)) { in[i].expand(*it);in.erase(it);return true; }
	}
	return false;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#else
	freopen("farmer.in","r",stdin);
	freopen("farmer.out","w",stdout);
#endif // MengLan

	scanf("%d%d%d",&x,&y,&n);
	FOR(i,0,n) {
		int a,b,r;scanf("%d%d%d",&a,&b,&r);
		in.pb({ a-r,b-r,a+r,b+r,true});
	}
	for(;;) {
		bool ok=false;
		for(int i=0;i<in.size();++i) if(in[i].use)
			for(int j=0;j<in.size();++j) if(j!=i&&in[j].use&&in[i].touch(in[j])) {
				in[i].expand(in[j]);
				in[j].use=false;
				ok=true;
			}
		if(!ok) break;
	}
	int ans=x*y;
	for(auto &v:in) if(v.use) ans-=v.area();
	printf("%d\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
