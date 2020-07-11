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
	bool inside(const P &r) { return r.fi<x2&&r.fi>x&&r.se<y2&&r.se>y; }
};
std::vector<Lan> v;
int n,h,w;

int main() {
#ifdef MengLan
	int Beginning=clock();
#else
	freopen("cricket.in","r",stdin);
	freopen("cricket.out","w",stdout);
#endif // MengLan

	scanf("%d%d%d",&n,&w,&h);
	v.clear();
	v.pb({ 0,0,w,h });
	//PV(1);
	FOR(i,0,n) {
		P in;
		scanf("%d%d",&in.fi,&in.se);
		int sz=v.size();
		//PV(i);
		FOR(i,0,sz) if(v[i].inside(in)) {
			v.pb({ v[i].x,v[i].y,in.fi,v[i].y2 });
			v.pb({ in.fi,v[i].y,v[i].x2,v[i].y2 });
			v.pb({ v[i].x,v[i].y,v[i].x2,in.se });
			v.pb({ v[i].x,in.se,v[i].x2,v[i].y2 });
			v[i]={ 0,0,0,0 };
		}
	}
	int ans=0;
	P con;
	for(auto &i:v) {
		//printf("x:%d y:%d x2:%d y2:%d\n",i.x,i.y,i.x2,i.y2);
		int t=std::min(i.x2-i.x,i.y2-i.y);
		if(ans<t) {
			ans=t;con={ i.x,i.y };
		}
	}
	printf("%d %d %d\n",con.fi,con.se,ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
/*
7 10 7
3 2
4 2
7 0
7 3
4 5
2 4
1 7

*/