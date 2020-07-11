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

const int maxn = 500 + 5;
const int INF=1e9;
std::vector<int> G[maxn];
char s[maxn];
int n,m;


// 二分图最大基数匹配，邻接矩阵写法
struct BPM {
  int n, m;               // 左右顶点个数
  int G[maxn][maxn];      // 邻接表
  int left[maxn];         // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];           // T[i]为右边第i个点是否已标记

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    memset(G, 0, sizeof(G));
  }

  bool match(int u){
    for(int v = 0; v < m; v++) if(G[u][v] && !T[v]) {
      T[v] = true;
      if (left[v] == -1 || match(left[v])){
        left[v] = u;
        return true;
      }
    }
    return false;
  }

  // 求最大匹配
  int solve() {
    memset(left, -1, sizeof(left));
    int ans = 0;
    for(int u = 0; u < n; u++) { // 从左边结点u开始增广
      memset(T, 0, sizeof(T));
      if(match(u)) ans++;
    }
    return ans;
  }

};

BPM solver;

bool vis[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    For(i,1,n) scanf(" %c",s+i);
    FOR(i,0,m){
        int u,v;scanf("%d%d",&u,&v);
        if(s[u]==s[v]) break;
        G[u].pb(v);
        G[v].pb(u);
    }
    solver.init(n,n);
    For(i,1,n){
        memset(vis,0,sizeof(vis));
        for(auto &v:G[i]) vis[v]=true;
        For(j,1,n) if(!vis[j]&&(s[i]=='S'&&s[j]=='K'||s[i]=='K'&&s[j]=='S')) solver.G[i][j]=1;
    }
    int cnt=solver.solve();
    


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
