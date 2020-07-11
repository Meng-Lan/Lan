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

typedef __int128 lll;
const int maxn=1e5+10;
lll c1[maxn],c2[maxn];
int in[maxn];
int n;

inline int lowbit(int x){return x&-x;}
void add(lll *c,int x,lll y){
    while(x<=n){c[x]+=y;x+=lowbit(x);}
}
lll sum(lll *c,int x){
    lll ret=0;
    while(x){ret+=c[x];x-=lowbit(x);}
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int q;scanf("%d%d",&n,&q);
    For(i,1,n){
        scanf("%d",in+i);
        add(c1,i,in[i]);
        add(c2,i,1LL*in[i]*(n+1-i));
    }
    while(q--){
        int a;scanf("%d",&a);
        if(a==1){
            int l,r;scanf("%d%d",&l,&r);
            lll sum1=sum(c1,r)-sum(c1,l-1);
            lll sum2=sum(c2,r)-sum(c2,l-1);
            // PV(sum1)PV(sum2);
            ll ans=sum2-sum1*(n-r);
            // PV(ans);
            printf("%lld\n",ans);
        }
        else{
            int x,y;scanf("%d%d",&x,&y);
            add(c1,x,-in[x]);add(c2,x,-1LL*in[x]*(n+1-x));
            add(c1,x,y);add(c2,x,1LL*y*(n+1-x));
            in[x]=y;
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
