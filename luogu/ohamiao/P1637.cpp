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

const int maxn=30000+10;
int in[maxn],h[maxn];
int c1[maxn],c2[maxn];
int n;

int lowbit(int x){return x&-x;}
void add1(int x,int v){while(x<=n){c1[x]+=v;x+=lowbit(x);}}
void add2(int x,int v){while(x){c2[x]+=v;x-=lowbit(x);}}
int sum1(int x){
    int ret=0;
    while(x){ret+=c1[x];x-=lowbit(x);}
    return ret;
}
int sum2(int x){
    int ret=0;
    while(x<=n){ret+=c2[x];x+=lowbit(x);}
    return ret;
}


int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d",&n);
    For(i,1,n) scanf("%d",in+i),h[i]=in[i];
    std::sort(h+1,h+n+1);
    For(i,1,n) {
        in[i]=std::lower_bound(h+1,h+n+1,in[i])-h;
        add2(in[i],1);
    }
    ll ans=0;
    For(i,1,n){
        add2(in[i],-1);
        ans+=sum1(in[i]-1)*sum2(in[i]+1);
        add1(in[i],1);
    }
    printf("%lld\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
