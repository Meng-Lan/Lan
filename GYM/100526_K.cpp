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

const int maxn=35;
char s[15][maxn];
int n,m,src[15];
bool vis[15][maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        FOR(i,0,n) scanf(" %s%d",s[i],src+i);
        FOR(i,0,n) FOR(j,0,m) vis[i][j]=s[i][j]=='1';
        //FOR(i,0,n) FOR(j,0,m) printf("%d%c",vis[i][j],j!=m-1?' ':'\n');
        std::map<std::vector<int>,std::vector<int>> mp;
        int l=m/2,r=m-l;
        //PV(l)PV(r);
        FOR(i,0,(1<<l)){
            std::vector<int> v;
            FOR(j,0,n){
                int res=0;
                FOR(k,0,l) if(vis[j][k]==((i>>k)&1)) ++res;
                v.pb(res);
            }
            //PV(i)
            //PA(v,0,n)
            mp[v].pb(i);
        }
        int ans=0;
        P tmp;
        FOR(i,0,(1<<r)){
            std::vector<int> v;
            FOR(j,0,n){
                int res=0;
                FOR(k,0,r) if(vis[j][k+l]==((i>>k)&1)) ++res;
                v.pb(src[j]-res);
            }
            //PV(i)
            //PA(v,0,n)
            int t=mp[v].size();
            if(ans==0&&t==1) tmp=P(mp[v][0],i);
            ans+=t;
        }
        if(ans==1){
            FOR(i,0,l) printf("%d",((tmp.fi>>i)&1));
            FOR(i,0,r) printf("%d",((tmp.se>>i)&1));
            printf("\n");
        }
        else printf("%d solutions\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
