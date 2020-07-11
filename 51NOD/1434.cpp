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

const int maxn=1e6+10;
int n;
bool vis[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	std::vector<int> p;
	FOR(i,2,maxn) if(!vis[i]){
		p.pb(i);
		for(int j=i+i;j<maxn;j+=i) vis[j]=true;
	}
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		std::vector<int> lcm(p.size(),0);
		FOR(i,0,p.size()) if(p[i]<=n){
			for(int j=p[i];j<=n;j+=p[i]){
				int k=j,cnt=0;
				while(k%p[i]==0) {k/=p[i];++cnt;}
				lcm[i]=std::max(lcm[i],cnt);
			}
		}
		int m=n+1;
		FOR(i,0,lcm.size()) if(lcm[i]){
			int v=pow(p[i],lcm[i]);
			int t=(n+v)/v*v;
			//printf("v:%d t:%d\n",v,t);
			m=std::max(t,m);
		}
		printf("%d\n",m);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
