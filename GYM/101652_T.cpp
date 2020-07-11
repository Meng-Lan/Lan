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

const int maxn=5e3+10;
std::vector<int> G[maxn];
int n,m,k;
int s,t;
int a[maxn],b[maxn],c[maxn],d[maxn];
std::vector<int> v;

bool vis[maxn];
bool BFS(int r){
    std::queue<int> q;
    memset(vis,0,sizeof(vis));
    q.push(s);
    while(!q.empty()){
        int x=q.front();q.pop();
        if(x==t) return true;
        vis[x]=true;
        for(auto i:G[x]){
            int v=b[i];
            if(vis[v]) continue;
            if(c[i]<=r&&r<=d[i]) q.push(v);
        }
    }
    return false;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d%d%d",&n,&m,&k,&s,&t);
    FOR(i,0,m) {
        scanf("%d%d%d%d",a+i,b+i,c+i,d+i);
        G[a[i]].pb(i);
        v.pb(c[i]-1);v.pb(d[i]);
    }
    std::sort(v.begin(),v.end());
    v.resize(std::unique(v.begin(),v.end())-v.begin());
    int ans=0;
    FOR(i,1,v.size()){
        if(BFS(v[i])) ans+=v[i]-v[i-1];
    }
    cout<<ans<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
