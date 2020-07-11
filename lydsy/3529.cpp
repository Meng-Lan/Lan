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
int c[maxn],mu[maxn],p[maxn];
bool vis[maxn];
int sz,up;
int ans[maxn];
struct Q{
    int n,m,q,id;
    void input(int i){scanf("%d%d%d",&n,&m,&q);id=i;}
    bool operator<(const Q &rhs)const{return q<rhs.q;}
}in[maxn];
struct F{
    int f,i;
    bool operator<(const F &rhs)const{return f<rhs.f||f==rhs.f&&i<rhs.i;}
}f[maxn];
void init(){
    mu[1]=1;
    for(int i=2;i<up;++i){
        if(!vis[i]){
            p[sz++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<sz&&p[j]*i<=up;++j){
            vis[p[j]*i]=true;
            if(i%p[j]==0){mu[p[j]*i]=0;break;}
            mu[p[j]*i]=-mu[i];
        }
    }
    For(i,1,up) f[i].i=i;
    For(i,1,up) for(int j=i;j<=up;j+=i) f[j].f+=i;
    std::sort(f+1,f+up+1);
}

inline int lowbit(int x){return x&-x;}
void add(int x,int v){while(x<=up){c[x]+=v;x+=lowbit(x);}}
int sum(int x){
    int ret=0;
    while(x){ret+=c[x];x-=lowbit(x);}
    return ret;
}

void read(int &n,int &m,int &a,int &id,Q q){
    n=q.n;m=q.m;a=q.q;id=q.id;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    FOR(i,0,T) {
        in[i].input(i);
        if(in[i].n>in[i].m) std::swap(in[i].n,in[i].m);
        up=std::max(up,in[i].n);
    }
    init();
    std::sort(in,in+T);
    int k=1;
    FOR(l,0,T){
        int n,m,a,id;read(n,m,a,id,in[l]);
        for(;k<=up&&f[k].f<=a;++k) {
            for(int j=f[k].i;j<=up;j+=f[k].i)
                add(j,f[k].f*mu[j/f[k].i]);
        }
        int last=0;
        int len=n;
        int ret=0;
        for(int i=1;i<=len;i=last+1){
            last=std::min(n/(n/i),m/(m/i));
            ret+=(n/i)*(m/i)*(sum(last)-sum(i-1));
        }
        ans[id]=ret;
    }
    FOR(i,0,T) printf("%d\n",ans[i]&0x7fffffff);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
/*
2
10000 10000 100000000
100000 100000 100000000

*/