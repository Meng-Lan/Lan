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
typedef std::pair<ll,ll> P;
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

const ll INF=1e18;
const int maxn=2e5+10;
struct Node {
	int l,r,id,max[3],min[3],d[3];
	int& operator[](int x) { return d[x]; }
	Node(int x=0,int y=0,int z=0) :l(0),r(0) { d[0]=x;d[1]=y;d[2]=z; }
}p[maxn];
int D,n,m,root;
int cmp(Node l,Node r) { return l[D]<r[D]; }
inline ll sqr(ll x) { return x*x; }

struct KDT {
	P ans;
	Node t[maxn],T;

	void up(int k) {
		Node &l=t[t[k].l],&r=t[t[k].r];
		for(int i=0;i<3;++i) {
			if(t[k].l) t[k].min[i]=std::min(t[k].min[i],l.min[i]),t[k].max[i]=std::max(t[k].max[i],l.max[i]);
			if(t[k].r) t[k].min[i]=std::min(t[k].min[i],r.min[i]),t[k].max[i]=std::max(t[k].max[i],r.max[i]);
		}
	}

	int build(int l,int r,int d) {
		D=d;
		int mid=(l+r)>>1;
		std::nth_element(p+l,p+mid,p+r+1,cmp);
		t[mid]=p[mid];t[mid].l=t[mid].r=0;
		for(int i=0;i<3;++i) t[mid].min[i]=t[mid].max[i]=t[mid][i];
		if(l<mid) t[mid].l=build(l,mid-1,(d+1)%3);
		if(r>mid) t[mid].r=build(mid+1,r,(d+1)%3);
		up(mid);
		return mid;
	}

	ll dis(Node k,Node t) {
		ll res=0;
		if(k.min[2]>t[2]) return INF;
		if(t[0]<k.min[0]) res+=sqr(k.min[0]-t[0]);
		if(t[0]>k.max[0]) res+=sqr(t[0]-k.max[0]);
		if(t[1]<k.min[1]) res+=sqr(k.min[1]-t[1]);
		if(t[1]>k.max[1]) res+=sqr(t[1]-k.max[1]);
		return res;
	}

	void query(int k,int now) {
		ll d0=sqr(t[k][0]-T[0])+sqr(t[k][1]-T[1]);
		if(d0<ans.fi&&t[k][2]<=T[2]) { ans.fi=d0;ans.se=k; }
		ll dl=INF,dr=INF;
		if(t[k].l) dl=dis(t[t[k].l],T);
		if(t[k].r) dr=dis(t[t[k].r],T);
		if(dl<dr) { if(dl<ans.fi) query(t[k].l,(now+1)%3);if(dr<ans.fi) query(t[k].r,(now+1)%3); }
		else { if(dr<ans.fi) query(t[k].r,(now+1)%3);if(dl<ans.fi) query(t[k].l,(now+1)%3); }
	}
	int query(Node p) {
		T=p;ans.fi=INF;
		query(root,0);
		return ans.se;
	}
}kd;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		For(i,1,n) scanf("%d%d%d",&p[i].d[0],&p[i].d[1],&p[i].d[2]);
		root=kd.build(1,n,0);
		FOR(i,0,m) {
			int x,y,z;scanf("%d%d%d",&x,&y,&z);
			int id=kd.query(Node(x,y,z));
			printf("%d %d %d\n",kd.t[id][0],kd.t[id][1],kd.t[id][2]);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
