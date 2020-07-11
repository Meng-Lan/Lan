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

struct Lan{
    int x,y;
    Lan(int x,int y):x(x),y(y){}
    Lan():Lan(0,0){}
    bool operator==(const Lan &rhs)const{return x*rhs.y==y*rhs.x;}
    bool operator<(const Lan &rhs)const{return x<rhs.x||x==rhs.x&&y<rhs.y;}
}in[50],xy;
int n;


int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;cin>>T;
    while(T--){
        cin>>n>>xy.x>>xy.y;
        FOR(i,0,n) cin>>in[i].x>>in[i].y;
        int l=n>>1,r=n-l;
        std::map<Lan,int> ls;
        ll ans=0;
        int max=0;
        FOR(i,0,n) max+=in[i].x;
        if(xy.x!=0) max=max/xy.x+(max%xy.x>0);
        else max=1;
        FOR(i,1,(1<<l)){
            Lan t;
            FOR(j,0,l) if(i&(1<<j)){t.x+=in[j].x;t.y+=in[j].y;}
            if(t==xy) ++ans;
            ls[t]++;
        }
        FOR(i,1,(1<<r)){
            Lan t;
            FOR(j,0,r) if(i&(1<<j)){t.x+=in[j+l].x;t.y+=in[j+l].y;}
            if(t==xy) ++ans;
            For(i,1,max){
                Lan v(xy.x*i-t.x,xy.y*i-t.y);
                if(v.x>=0&&v.y>=1&&ls.count(v)) ans+=ls[v];
            }
        }
        cout<<ans<<endl;
    }


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
