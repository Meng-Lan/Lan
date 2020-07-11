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

const int INF=1e9;
const int maxn=1e6+10;
int n,k;
int min[maxn<<2],max[maxn<<2];

void build(int rt,int l,int r){
    if(l==r) {read(min[rt]),max[rt]=min[rt];return;}
    int m=(l+r)>>1;
    build(rt<<1,l,m);
    build(rt<<1|1,m+1,r);
    min[rt]=std::min(min[rt<<1],min[rt<<1|1]);
    max[rt]=std::max(max[rt<<1],max[rt<<1|1]);
}

int L,R,Min,Max;
int ans[maxn][2];
void query(int rt,int l,int r){
    if(L<=l&&r<=R){Min=std::min(min[rt],Min);Max=std::max(max[rt],Max);return;}
    int m=(l+r)>>1;
    if(L<=m) query(rt<<1,l,m);
    if(R>m) query(rt<<1|1,m+1,r);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    read(n),read(k);
    build(1,1,n);
    For(i,k,n){
        Min=INF;
        Max=-INF;
        L=i-k+1,R=i;
        query(1,1,n);
        ans[i][0]=Min;
        ans[i][1]=Max;
        //printf("L:%d R:%d min:%d max:%d\n",L,R,Min,Max);
    }
    For(i,k,n) printf("%d%c",ans[i][0]," \n"[i==n]);
    For(i,k,n) printf("%d%c",ans[i][1]," \n"[i==n]);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
