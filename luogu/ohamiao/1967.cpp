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
const int logn=20;
struct Edge{
    int u,v,z;
    void input(){scanf("%d%d%d",&u,&v,&z);}
    bool operator<(const Edge &rhs)const{return z>rhs.z;}
};
std::vector<P> G[maxn];
std::vector<Edge> edges;
int n,m;
int p[maxn];
int f[maxn],inc[maxn][logn];
int z[maxn],inz[maxn][logn];
int h[maxn];

int find(int x){return x==p[x]?x:find(p[x]);}

void dfs(int u,int fa){
    //if(G[u].size()==1) return;
    for(auto &v:G[u]) if(v.first!=fa) {z[v.first]=v.second;f[v.first]=u;h[v.first]=h[u]+1;dfs(v.first,u);}
}

void init(){
    For(i,1,n){
        inc[i][0]=f[i];inz[i][0]=z[i];
        for(int j=1;(1<<j)<n;++j) inc[i][j]=-1;
    }
    for(int j=1;(1<<j)<n;++j){
        For(i,1,n) if(inc[i][j-1]!=-1){
            int a=inc[i][j-1];
            inc[i][j]=inc[a][j-1];
            inz[i][j]=std::min(inz[i][j-1],inz[a][j-1]);
        }
    }
}

int solve(int p,int q){
    if(find(p)!=find(q)) return -1;
    int log;
    if(h[p]<h[q]) std::swap(p,q);
    for(log=1;(1<<log)<=h[p];++log);--log;

    int ans=1e9;
    for(int i=log;i>=0;--i) if(h[p]-(1<<i)>=h[q]){ans=std::min(ans,inz[p][i]);p=inc[p][i];}

    if(p==q) return ans;

    for(int i=log;i>=0;--i) if(inc[p][i]!=0&&inc[p][i]!=inc[q][i]){
        ans=std::min(ans,inz[p][i]);p=inc[p][i];
        ans=std::min(ans,inz[q][i]);q=inc[q][i];
    }

    ans=std::min(ans,z[p]);
    ans=std::min(ans,z[q]);
    return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    FOR(i,0,m){Edge e;e.input();edges.pb(e);}
    std::sort(edges.begin(),edges.end());
    For(i,1,maxn) p[i]=i;
    FOR(i,0,edges.size()){
        int u=find(edges[i].u),v=find(edges[i].v);
        if(u!=v){
            p[u]=v;
            G[edges[i].u].pb({edges[i].v,edges[i].z});
            G[edges[i].v].pb({edges[i].u,edges[i].z});
        }
    }
    For(i,1,n) if(!h[i]){
        dfs(i,-1);
        z[i]=maxn;
    }
    init();
    // For(i,1,n) {PV(f[i]);PV(z[i]);}
    int q;scanf("%d",&q);
    while(q--){
        int u,v;scanf("%d%d",&u,&v);
        printf("%d\n",solve(u,v));
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
