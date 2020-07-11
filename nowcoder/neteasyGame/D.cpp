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

const int maxn=1e4+10;
int degree[maxn];
int f[maxn];

int find(int x){return f[x]==x?x:f[x]=find(f[x]);}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        memset(degree,0,sizeof(degree));
        FOR(i,0,maxn) f[i]=i;
        FOR(i,0,n){
            int u,v;scanf("%d%d",&u,&v);
            assert(u>=0&&u<maxn);
            assert(v>=0&&v<maxn);
            int x=find(u),y=find(v);
            if(x!=y) f[x]=y;
            degree[u]++;
            degree[v]++;
        }
        int tmp=0;
        std::set<int> s;
        FOR(i,0,maxn) if(degree[i]>0){
            if(degree[i]&1) ++tmp;
            s.insert(find(i));
        }
        if((tmp==0||tmp==2)&&s.size()==1) puts("yes");
        else puts("no");
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
