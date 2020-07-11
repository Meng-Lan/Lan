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

const int maxn=2e6;
bool vis[maxn+10];

void prim(std::vector<int> &p){
    int m=sqrt(maxn+0.5);
    memset(vis,0,sizeof(vis));
    for(int i=2;i<=m;++i) if(!vis[i]){
        for(int j=i*i;j<=maxn;j+=i) vis[j]=true;
    }
    For(i,2,maxn) if(!vis[i]) p.pb(i);
}
int n,in[111111],ans[111111],nxt[211111];

inline bool check(std::vector<int> &p,int t){
    FOR(i,0,p.size()){
        if(p[i]>t) break;
        if(t%p[i]==0&&vis[i]) return false;
    }
    return true;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    std::vector<int> p;
    prim(p);
    scanf("%d",&n);
    FOR(i,0,n) scanf("%d",in+i);
    memset(vis,0,sizeof(vis));
    bool big=false;
    int t=0;
    FOR(i,0,n){
        if(!big){
            if(check(p,in[i])) {
                ans[i]=in[i];
                FOR(j,0,p.size()){
                    if(p[j]>in[i]) break;
                    if(in[i]%p[j]==0) vis[j]=true;
                }
            }
            else{
                int res=in[i];
                bool ok=false;
                do{
                    ++res;
                    ok=true;
                    FOR(j,0,p.size()){
                        if(p[j]>100000) break;
                        if(res%p[j]==0&&vis[j]) {ok=false;break;}
                    }
                }while(!ok);
                ans[i]=res;
                FOR(j,0,p.size()){
                    if(p[j]>res) break;
                    if(res%p[j]==0) vis[j]=true;
                }
                big=true;
            }
        }
        else{
            while(vis[t]) ++t;
            ans[i]=p[t];
            vis[t]=true;
        }
    }
    FOR(i,0,n) printf("%d%c",ans[i],i==n-1?'\n':' ');   

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
