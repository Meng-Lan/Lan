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
const int maxm=2e5+10;
const int maxa=1e6+10;
int n,m;
int pre[maxa];
int c[maxa];
int in[maxn];
struct Lan{
	int l,r,id;
	bool operator<(const Lan &rhs)const{return r<rhs.r||r==rhs.r&&l<rhs.l;}
}q[maxm];
int ans[maxn];

int t[maxa<<2],add[maxa<<2];

void pushdown(int rt){
	if(add[rt]){
		add[rt<<1]+=add[rt];
		add[rt<<1|1]+=add[rt];
		add[rt]=0;
	}
}

void maintain(int rt){
	t[rt]=t[rt<<1]+t[rt<<1|1]+add[rt<<1]+add[rt<<1|1];
}

void update(int rt,int l,int r,int L,int R){
	if(L<=l&&r<=R){++add[rt];return;}
	pushdown(rt);
	int m=(l+r)>>1;
	if(L<=m) update(rt<<1,l,m,L,R);
	if(R>m) update(rt<<1|1,m+1,r,L,R);
}

int query(int rt,int l,int r,int x){
	if(l==r) return add[rt];
	pushdown(rt);
	int m=(l+r)>>1;
	if(x<=m) return query(rt<<1,l,m,x);
	return query(rt<<1|1,m+1,r,x);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d",&n);
	For(i,1,n){
		scanf("%d",in+i);
		pre[i]=c[in[i]];
		c[in[i]]=i;
	}
	scanf("%d",&m);
	FOR(i,0,m) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
    std::sort(q,q+m);
	int j=0;
	For(i,1,n){
		update(1,1,maxa,pre[i]+1,i);
        // printf("pre[i]=%d\n",pre[in[i]]+1);
		while(j<m&&q[j].r==i){
			ans[q[j].id]=query(1,1,maxa,q[j].l);
            // printf("id:%d l:%d r:%d ans:%d\n",q[j].id,q[j].l,q[j].r,ans[q[j].id]);
			++j;
		}
	}
	FOR(i,0,m) printf("%d\n",ans[i]);
	
#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
