#include<bits/stdc++.h>
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
const int logn=25;
struct Task{
    int t,p,add;
    Task(int t,int p,int add):t(t),p(p),add(add){}
    Task():Task(0,0,0){}
    bool operator<(const Task &rhs){return t<rhs.t;}
}in[maxn<<1];
struct Lan{
    int l,r,cnt;
    ll sum;
}t[maxn*logn*2];
int n,m;
ll pre;
int r[maxn],sz;

void update(int &rt,int l,int r,int p,int add){
    t[++sz]=t[rt];
    t[sz].sum+=add*p;
    t[sz].cnt+=add;
    rt=sz;
    if(l==r) return;
    int m=l+(r-l)/2;
    if(p<=m) update(t[rt].l,l,m,p,add);
    else update(t[rt].r,m+1,r,p,add);
}

ll query(int rt,int l,int r,int k){
    if(l==r){
        //printf("rt:%d l:%d r:%d k:%d sum:%lld cnt:%d\n",rt,l,r,k,t[rt].sum,t[rt].cnt);
        return t[rt].sum/t[rt].cnt*k;
    }
    if(t[rt].cnt==k) return t[rt].sum;
    int m=l+(r-l)/2;
    if(t[rt].l&&t[t[rt].l].cnt>=k) return query(t[rt].l,l,m,k);
    ll ans=0;
    if(t[rt].l){ans=t[t[rt].l].sum;k-=t[t[rt].l].cnt;}
    if(k) ans+=query(t[rt].r,m+1,r,k);
    return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    int cnt=0,R=0;
    FOR(i,0,n){
        int s,e,p;scanf("%d%d%d",&s,&e,&p);
        in[cnt++]=Task(s,p,1);
        in[cnt++]=Task(e+1,p,-1);
        R=std::max(R,p);
    }
    std::sort(in,in+cnt);
    //FOR(i,0,cnt) printf("in[%d]=%d %d %d\n",i,in[i].t,in[i].p,in[i].add);
    int j=0;
    For(i,1,m){
        r[i]=r[i-1];
        while(in[j].t==i){
            update(r[i],1,R,in[j].p,in[j].add);++j;
        }
        //PV(j);
    }
    pre=1;
    FOR(i,0,m){
        int x,a,b,c;scanf("%d%d%d%d",&x,&a,&b,&c);
        int k=(pre%c*a+b)%c+1;
        //PV(i);
        //printf("query x:%d k:%d root sum:%d cnt:%d\n",x,k,t[r[x]].sum,t[r[x]].cnt);
        if(t[r[x]].cnt<=k) printf("%lld\n",(pre=t[r[x]].sum));
        else printf("%lld\n",(pre=query(r[x],1,R,k)));
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
