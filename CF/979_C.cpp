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

const int maxn=5e5+10;
std::vector<int> G[maxn];
int n,x,y;

bool vis[maxn];
int bfs(int u,int fa,int d){
    std::queue<int> q;
    q.push(u);
    int ret=0;
    while(!q.empty()){
        int v=q.front();q.pop();
        if(v==d) return 0;
        if(vis[v]) continue;
        vis[v]=true;
        ++ret;
        for(auto it:G[v]) if(it!=fa) q.push(it);
    }
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d",&n,&x,&y);
    FOR(i,1,n){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);
        G[v].pb(u);
    }
    ll ans=1LL*n*(n-1);
    ll tx=0,ty=0;
    for(auto &v:G[x]){
        int t=bfs(v,x,y);
        //printf("x:%d v:%d t:%d\n",x,v,t);
        if(t>0) tx+=t;
    }
    memset(vis,0,sizeof(vis));
    for(auto &v:G[y]){
        int t=bfs(v,y,x);
        //printf("y:%d v:%d t:%d\n",y,v,t);
        if(t>0) ty+=t;
    }
    ++tx;++ty;
    ans-=tx*ty;
    cout<<ans<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
