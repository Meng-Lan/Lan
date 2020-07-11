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
int n;
struct Node{
    int l,r,v;
}t[maxn*20];
int sz;
struct IN{
    int x,y,v;
    bool operator<(const IN &rhs)const{return y>rhs.y;}
}in[maxn];
int val[maxn*2],cnt;
std::vector<IN> G[maxn];

int getnum(int x){return std::lower_bound(val,val+cnt,x)-val;}

int getNode(){++sz;t[sz].l=t[sz].r=t[sz].v=0;return sz;}

void update(int &rt,int l,int r,int x,int y){
    if(!rt) rt=getNode();
    if(l==r){t[rt].v=std::max(y,t[rt].v);return;}
    int m=l+(r-l)/2;
    if(x<=m) update(t[rt].l,l,m,x,y);
    else update(t[rt].r,m+1,r,x,y);
    t[rt].v=std::max(t[t[rt].l].v,t[t[rt].r].v);
}

int query(int &rt,int l,int r,int x,int y){
    // if(!rt) rt=getNode();
    if(x<=l&&r<=y) return t[rt].v;
    int m=l+(r-l)/2;
    int ret=0;
    if(x<=m&&t[rt].l) ret=std::max(ret,query(t[rt].l,l,m,x,y));
    if(y>m&&t[rt].r) ret=std::max(ret,query(t[rt].r,m+1,r,x,y));
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        cnt=0;
        sz=0;
        FOR(i,0,n){
            scanf("%d%d%d",&in[i].x,&in[i].y,&in[i].v);
            val[cnt++]=in[i].x;
            val[cnt++]=in[i].y;
        }
        std::sort(val,val+cnt);
        cnt=std::unique(val,val+cnt)-val;
        FOR(i,0,n){
            G[getnum(in[i].x)].pb(in[i]);
        }
        int root=0;
        FOR(i,0,cnt) if(!G[i].empty()){
            int ret=0;
            std::sort(G[i].begin(),G[i].end());
            for(auto &v:G[i]){
                ret=0;
                if(root&&getnum(v.y)-1>=0) ret=query(root,0,cnt,0,getnum(v.y)-1);
                update(root,0,cnt,getnum(v.y),ret+v.v);
            }
        }
        FOR(i,0,cnt) G[i].clear();
        int ans=query(root,0,cnt,0,cnt);
        printf("%d\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
