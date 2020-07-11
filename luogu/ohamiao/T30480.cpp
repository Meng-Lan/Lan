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
const int N=5e5;
int c[maxn];
int n,q;

inline int lowbit(int x){return x&-x;}
void add(int x,int v){while(x<=N){c[x]+=v;x+=lowbit(x);}};
int sum(int x){
    int ret=0;
    while(x){ret+=c[x];x-=lowbit(x);}
    return ret;
}
int find(int x){return sum(x)-sum(x-1);}

int main() {
#ifdef MengLan
	//int Beginning=clock();
	freopen("recall10.in","r",stdin);
	freopen("recall10.out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&q);
    assert(n>=1&&n<=2e5&&q>=1&&q<=N);
    FOR(i,0,n){int x;scanf("%d",&x);assert(x>=1&&x<=N);add(x,1);}
    while(q--){
        int t,x;scanf("%d%d",&t,&x);
        assert(t>=1&&t<=4&&x>=1&&x<=N);
        if(t==1&&find(x)) add(x,-1);
        if(t==2&&!find(x)) add(x,1);
        if(t==3) printf("%d\n",sum(x));
        if(t==4) printf("%d\n",sum(N)-sum(x-1));
    }

#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
    //system("pause");
#endif // MengLan
	return 0;
}
