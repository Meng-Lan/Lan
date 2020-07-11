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

const int maxm=2e5+10;
int m,n;
char s[maxm];
bool ec[maxm*10];
bool dc[maxm*10];
int ecs,dcs;

struct Lan{
    bool end;
    char c;
    int nxt[2];
}trie[maxm];
int cnt,root;

void init(){
    memset(trie,0,sizeof(Lan)*(cnt+10));
}

void add(int v,char *s){
    char *c=s;
    int idx=root;
    while(*c!='\0'){
        int &t=trie[idx].nxt[*c-'0'];
        if(!t) t=++cnt;
        idx=t;
        ++c;
    }
    trie[idx].end=true;
    trie[idx].c=v;
    // putchar(v);puts("");
}

inline int hto(char c){
    if(isdigit(c)) return c-'0';
    else return tolower(c)-'a'+10;
}

int ans=0;
void encode(){
    int begin=0,end=0;
    dcs=0;
    char *c=s;
    ans=0;
    while(*c!='\0'){
        int v=hto(*c);
        ++c;
        for(int i=3;i>=0;--i) if((v>>i)&1) ec[end++]=true;else ec[end++]=false;
        // for(int i=3;i>=0;--i) if((v>>i)&1) putchar('1');else putchar('0');
        // putchar(' ');
    }
    // PV(end);
    // puts("");
    ans=0;
    while(begin<end){
        if(begin+9>end) break;
        int chk=0;
        FOR(i,begin,begin+8) if(ec[i]) ++chk;
        if((chk&1)!=ec[begin+8]){
            FOR(i,begin,begin+8) dc[dcs++]=ec[i];
            // FOR(i,begin,begin+8) if(ec[i]) putchar('1'); else putchar('0');
            ans+=2;
        }
        begin+=9;
    }
    // puts("");
}

void decode(){
    int idx=0,i=0;
    int ret=0;
    while(i<dcs){
        idx=trie[idx].nxt[dc[i]];
        if(trie[idx].end){
            putchar(trie[idx].c);++ret;
            idx=0;
            // printf("dcs:%d i:%d\n",dcs,i);
            if(ret==m) return;
        }
        ++i;
    }
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&m,&n);
        FOR(i,0,n){
            char in[15];
            int v;
            scanf("%d%s",&v,&in);
            add(v,in);
        }
        scanf("%s",s);
        encode();
        decode();
        puts("");
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
