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
const int maxm=3.5e7+10;
struct Trie{
    int ch[2],min;
    Trie(){ch[0]=ch[1]=0;min=maxm;}
}trie[maxm];
int sz=0;
std::vector<int> G[maxn];
int q;

void add(int v,int u){
    trie[v].min=std::min(trie[v].min,u);
    for(int i=18;i>=0;--i){
        int c=(u>>i)&1;
        if(!trie[v].ch[c]) trie[v].ch[c]=sz++;
        v=trie[v].ch[c];
        trie[v].min=std::min(trie[v].min,u);
    }
}

int query(int x,int k,int s){
    if(x%k!=0||trie[k].min>s-x) return -1;
    int ret=0;
    int u=k;
    for(int i=18;i>=0;--i){
        int c=(x>>i)&1;
        if(trie[u].ch[c^1]&&trie[trie[u].ch[c^1]].min+x<=s){
            ret+=(c^1)<<i;
            u=trie[u].ch[c^1];
        }
        else{
            ret+=c<<i;
            u=trie[u].ch[c];
        }
    }
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    FOR(i,1,maxn) for(int j=i;j<maxn;j+=i) G[j].pb(i);
    sz=maxn;
    scanf("%d",&q);
    while(q--){
        int t;scanf("%d",&t);
        if(t==1) {
            int u;scanf("%d",&u);
            for(auto v:G[u]) add(v,u);
        }
        else{
            int x,k,s;scanf("%d%d%d",&x,&k,&s);
            printf("%d\n",query(x,k,s));
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
