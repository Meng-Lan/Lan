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

const int logn=20;
const int maxn=5e4+10;
int root=0;
const int INF=1e9+10;
struct Lan{
    int l,r;
    int sz,t;
    int max,min;
}t[maxn*logn];
int sz,n;

std::vector<int> v;
int getID(int x){return std::lower_bound(v.begin(),v.end(),x)-v.begin();}

std::vector<P> in;
std::vector<P> x[maxn];

bool queryMax(int rt,int l,int r,int max){
    if(!rt) return false;
    if(l>=max) return t[rt].max>max;
    int m=l+(r-l)/2;
    bool ret=queryMax(t[rt].r,m+1,r,max);
    if(!ret&&max<=m) ret=queryMax(t[rt].l,l,m,max);
    return ret;
}

int findMin(int rt,int l,int r,int L,int max){
    if(!rt) return -1;
    if(l==r) return l;
    int m=l+(r-l)/2;
    if(t[rt].l>0&&t[t[rt].l].min<max) return findMin(t[rt].l,l,m,L,max);
    if(L>m&&t[rt].r&&t[t[rt].r].min<max) return findMin(t[rt].r,m+1,r,L,max);
    return -1;
}

inline void maintain(int rt){
    int L=t[rt].l,R=t[rt].r;
    t[rt].min=std::min(t[L].min,t[R].min);
    t[rt].max=std::max(t[L].max,t[R].max);
    t[rt].sz=t[L].sz+t[R].sz;
}

void add(int &rt,int l,int r,int x,int y,int op){
    if(!rt) {rt=++sz;t[rt].max=0;t[rt].min=INF;}
    // printf("add rt:%d l:%d r:%d x:%d y:%d op:%d\n",rt,l,r,x,y,op);
    if(l==r){
        if(op==1){t[rt].min=t[rt].max=t[rt].t=y;t[rt].sz=1;}
        else if(op==-1){t[rt].max=0;t[rt].min=INF;t[rt].sz=0;}
        return;
    }
    int m=l+(r-l)/2;
    if(x<=m) add(t[rt].l,l,m,x,y,op);
    else add(t[rt].r,m+1,r,x,y,op);
    // PV(t[rt].l);
    maintain(rt);
}

int findR(int rt,int l,int r,int R,int tim){
    if(!rt) return -1;
    if(l==r) return l;
    int m=l+(r-l)/2;
    int ret=0;
    if(R>m&&t[rt].r&&t[t[rt].r].max>tim&&(ret=findR(t[rt].r,m+1,r,R,tim))!=-1) return ret;
    if(t[rt].l&&t[t[rt].l].max>tim&&(ret=findR(t[rt].l,l,m,R,tim))!=-1) return ret;
    return -1;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d",&n);
    FOR(i,0,n){
        int x,y;scanf("%d%d",&x,&y);
        in.pb({x,y});
        v.pb(x);
    }
    std::sort(v.begin(),v.end());
    int len=std::unique(v.begin(),v.end())-v.begin();
    v.resize(len);
    FOR(i,0,n) x[getID(in[i].fi)].pb({in[i].se,i+1});
    ll ans=0;
    t[0].min=INF;
    for(int i=v.size()-1;i>=0;--i){
        // PV(v[i]);
        if(i+1<v.size()) ans+=(ll)(v[i+1]-v[i])*t[root].sz;
        // PV(ans)
        if(!x[i].empty()) std::sort(x[i].begin(),x[i].end());
        for(int j=x[i].size()-1;j>=0;--j){
            bool ok=queryMax(root,0,INF,x[i][j].fi);
            if(ok) continue;
            int ret;
            while((ret=findMin(root,0,INF,x[i][j].fi,x[i][j].se))!=-1){
                // PV(ret)
                add(root,0,INF,ret,0,-1);
            }
            // PV(ret)
            add(root,0,INF,x[i][j].fi,x[i][j].se,1);
            int r=findR(root,0,INF,x[i][j].fi,x[i][j].se);
            if(r==-1) r=0;
            ans+=x[i][j].fi-r;
        }
        // PV(ans);
    }
    if(!v.empty()) ans+=(ll)v[0]*t[root].sz;
    // PV(ans);
    printf("%lld\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
