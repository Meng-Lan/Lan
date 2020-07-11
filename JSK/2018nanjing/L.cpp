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

const int N=1e5+5,M=2e5+5,K=11;
int n,m,k,s,t,a,b,c;
struct edge{
    int v,w,ne;
}e[M<<1];
int h[N],cnt=0;
inline void ins(int u,int v,int w){
    cnt++;
    e[cnt].v=v;e[cnt].w=w;e[cnt].ne=h[u];h[u]=cnt;
}
struct hn{
    int u,f;
    ll d;
    hn(int a=0,ll b=0,int c=0):u(a),f(c),d(b){}
    bool operator<(const hn &rhs)const{return d>rhs.d;}
};
ll d[N][K];
int done[N][K];
void bfs(){
    memset(d,127,sizeof(d));
    memset(done,0,sizeof(done));
    std::priority_queue<hn> q;
    q.push(hn(s,0,0));
    d[s][0]=0;
    while(!q.empty()){
        hn x=q.top();q.pop();
        int u=x.u,f=x.f;
        ll dis=x.d;
        if(done[u][f]) continue;
        done[u][f]=1;
        if(u==t){printf("%lld\n",dis);return;}
        for(int i=h[u];i;i=e[i].ne){
            int v=e[i].v,w=e[i].w;
            if(f<k&&!done[v][f+1]&&d[v][f+1]>dis){
                d[v][f+1]=dis;
                q.push(hn(v,dis,f+1));
            }
            if(!done[v][f]&&d[v][f]>dis+w){
                d[v][f]=dis+w;
                q.push(hn(v,d[v][f],f));
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    int T;scanf("%d",&T);
    while(T--){
        // n=read();m=read();k=read();
        memset(h,0,sizeof(h));
        cnt=0;
        memset(e,0,sizeof(e));
        scanf("%d%d%d",&n,&m,&k);
        s=1,t=n;
        for(int i=1;i<=m;i++){scanf("%d%d%d",&a,&b,&c);ins(a,b,c);}
        bfs();
    }
#ifdef MengLan
// printf("Time: %d\n",clock()-Beginning);
system("pause");
#endif // MengLan
    return 0;
}