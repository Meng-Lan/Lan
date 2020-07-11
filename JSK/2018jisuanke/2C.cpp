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

const int maxn=2e6+10;
const int sigma_size=26;
struct Trie{
    int ch[maxn][sigma_size];
    ll val[maxn];
    ll sum[maxn];
    int sz;
    Trie(){sz=1;memset(ch[0],0,sizeof(ch[0]));}
    int idx(char c){return c-'a';}

    void init(){sz=1;memset(ch,0,sizeof(ch[0]));}

    int insert(char *s,ll v){
        int u=0,n=strlen(s);
        for(int i=n-1;i>=0;--i){
            int c=idx(s[i]);
            if(!ch[u][c]){
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz]=0;
                sum[sz]=0;
                ch[u][c]=sz++;
            }
            u=ch[u][c];
            sum[u]+=v;
        }
        val[u]=v;
        return u;
    }

    int find(char *s,int n){
        int u=0;
        for(int i=n-1;i>=0;--i){
            int c=idx(s[i]);
            if(!ch[u][c]) return 0;
            u=ch[u][c];
        }
        return u;
    }

    void del(char *s){
        int u=0,n=strlen(s);
        int fs=find(s,n);
        int v=val[fs];
        if(fs||!v) puts("Empty");
        else{
            for(int i=n-1;i>=0;--i){
                int c=idx(s[i]);
                u=ch[u][c];
                sum[u]-=v;
            }
        }
        if(val[u]) val[u]=0;
    }

    void update(char *s,char *t){
        int ns=strlen(s),nt=strlen(t);
        int fs=find(s,ns),ft=find(t,nt);
        if(!fs||!sum[fs]) puts("Empty");
        else if(ft&&sum[ft]) puts("Conflict");
        else {
            ll v=sum[fs];
            int u=insert(t,v);
            memcpy(ch[u],ch[fs],sizeof(ch[u]));
            memset(ch[fs],0,sizeof(ch[fs]));
            u=0;
            for(int i=ns-1;i>=0;--i){
                int c=idx(s[i]);
                u=ch[u][c];
                sum[u]-=v;
            }
        }
    }
}trie;
char s[maxn],t[maxn];
int n;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        trie.init();
        while(n--){
            char cmd[10];
            scanf("%s",cmd);
            if(!strcmp(cmd,"insert")){
                ll v;scanf("%s%lld",s,&v);
                trie.insert(s,v);
            }
            else if(!strcmp(cmd,"delete")){
                scanf("%s",s);
                trie.del(s);
            }
            else if(!strcmp(cmd,"query")){
                scanf("%s",s);
                int n=strlen(s);
                int f=trie.find(s,n);
                if(!f||trie.sum[f]==0) puts("Empty");
                else printf("%lld\n",trie.sum[f]);
            }
            else{
                scanf("%s %s",s,t);
                trie.update(s,t);
            }
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
