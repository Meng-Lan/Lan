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

const int maxn=1e5+10;
int n,m;
P zw[maxn];
struct XY{
    int x,y,cost;
    void input(){scanf("%d%d",&x,&y);cost=200*x+3*y;}
    bool operator<(const XY &rhs)const{return cost<rhs.cost;}
}xy[maxn];

int t[444];
std::multiset<int> s[101];
void build(int rt,int l,int r){
    if(l==r){if(s[l].empty()) t[rt]=0;else t[rt]=*s[l].rbegin();return;}
    int m=l+(r-l)/2;
    build(rt<<1,l,m);
    build(rt<<1|1,m+1,r);
    t[rt]=std::max(t[rt<<1],t[rt<<1|1]);
}

int query(int rt,int l,int r,int x,int v){
    if(t[rt]<v) return -1;
    if(l==r) return l;
    int m=l+(r-l)/2;
    if(x<=m&&t[rt<<1]>=v) {
        int idx=query(rt<<1,l,m,x,v);
        if(idx>=x) return idx;
    }
    return query(rt<<1|1,m+1,r,x,v);
}

void update(int rt,int l,int r,int x,int v){
    if(l==r) {t[rt]=v;return;}
    int m=l+(r-l)/2;
    if(x<=m) update(rt<<1,l,m,x,v);
    else update(rt<<1|1,m+1,r,x,v);
    t[rt]=std::max(t[rt<<1],t[rt<<1|1]);
}


int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan
    
    scanf("%d%d",&n,&m);
    FOR(i,0,n) scanf("%d%d",&zw[i].fi,&zw[i].se);
    FOR(i,0,m) xy[i].input();
    FOR(i,0,n) s[zw[i].se].insert(zw[i].fi);
    std::sort(xy,xy+m);
    build(1,0,100);
    ll ans=0;
    int cnt=0;
    for(int i=m-1;i>=0;--i){
        int idx=query(1,0,100,xy[i].y,xy[i].x);
        if(idx==-1) continue;
        ans+=xy[i].cost;++cnt;
        auto it=s[idx].lower_bound(xy[i].x);
        s[idx].erase(it);
        if(s[idx].empty()) update(1,0,100,idx,0);
        else update(1,0,100,idx,*s[idx].rbegin());
    }
    printf("%d %lld\n",cnt,ans);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
