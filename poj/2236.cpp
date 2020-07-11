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

const int maxn=1111;
int f[maxn];
P in[maxn];
bool vis[maxn];

int sqr(int x){return x*x;}
int find(int x){return f[x]=(f[x]==x?x:find(f[x]));}
void uni(int x,int y){f[find(x)]=find(y);}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int n,d;scanf("%d%d",&n,&d);
    For(i,1,n) scanf("%d%d",&in[i].fi,&in[i].se);
    For(i,0,n) f[i]=i;
    char cmd[10];
    d*=d;
    while(scanf("%s",cmd)==1){
        if(cmd[0]=='O'){
            int x;scanf("%d",&x);
            if(vis[x]) continue;
            vis[x]=true;
            For(i,1,n) if(x!=i&&(sqr(in[i].fi-in[x].fi)+sqr(in[i].se-in[x].se)<=d&&vis[i])) uni(x,i);
        }
        else if(cmd[0]=='S'){
            int x,y;scanf("%d%d",&x,&y);
            if(find(x)==find(y)) printf("SUCCESS\n");
            else printf("FAIL\n");
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
