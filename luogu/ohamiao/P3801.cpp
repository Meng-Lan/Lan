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
int n,m,q;
int c[maxn],r[maxn];

int lowbit(int x){return x&-x;}
void add(int x,int v,int *C){
    while(x<maxn){C[x]+=v;x+=lowbit(x);}
}
int sum(int x,int *C){
    int ret=0;
    while(x){ret+=C[x];x-=lowbit(x);}
    return ret;
}
int find(int x,int *C){return sum(x,C)-sum(x-1,C);}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d",&n,&m,&q);
    while(q--){
        int t;scanf("%d",&t);
        if(t==1){
            int x,y;scanf("%d%d",&x,&y);
            if(!find(x,r)) add(x,1,r);else add(x,-1,r);
            if(!find(y,c)) add(y,1,c);else add(y,-1,c);
        }
        else{
            int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            ll x=sum(x2,r)-sum(x1-1,r),y=sum(y2,c)-sum(y1-1,c);
            ll ans=x*(y2-y1+1)+y*(x2-x1+1)-2*x*y;
            printf("%lld\n",ans);
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
