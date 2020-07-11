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
struct Lan{
    int x1,y1,x2,y2,k;
    Lan *ins,*del;
    Lan *inl,*inr;
    Lan *outl,*outr;
    void input(){scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);--x1;--x2;--y1;--y2;}
}list[maxn];
int *in[maxn];
int n,m,t;
Lan *ci[maxn],*cd[maxn];
Lan *ins[maxn],*del[maxn];
int vis[maxn],cnt[maxn];

int diff;
inline void add(int idx,int now){
    if(vis[now]==idx) {++cnt[now];return;}
    vis[now]=idx;cnt[now]=1;++diff;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d",&n,&m,&t);
    FOR(i,0,n) {
        in[i]=new int[m];
        FOR(j,0,m) scanf("%d",&in[i][j]);
    }
    FOR(i,0,t){
        list[i].input();
        list[i].ins=list[i].del=NULL;
        list[i].inl=list[i].inr=list[i].outl=list[i].outr=0;
        if(ins[list[i].x1]!=NULL) {list[i].ins=ins[list[i].x1];ins[list[i].x1]=&list[i];}
        else ins[list[i].x1]=&list[i];
        if(del[list[i].x2]!=NULL) {list[i].del=del[list[i].x2];del[list[i].x2]=&list[i];}
        else del[list[i].x2]=&list[i];
    }
    int ans=0;
    memset(vis,-1,sizeof(vis));
    FOR(i,0,n){
        Lan *top=ins[i];
        while(top!=NULL){
            // PV(top->k);
            top->inr=ci[top->y1];
            if(ci[top->y1]!=NULL) ci[top->y1]->inl=top;
            ci[top->y1]=top;

            top->outr=cd[top->y2];
            if(cd[top->y2]!=NULL) cd[top->y2]->outl=top;
            cd[top->y2]=top;

            top=top->ins;
        }
        FOR(j,0,m){
            top=ci[j];
            while(top!=NULL){
                add(i,top->k);
                top=top->inr;
            }
            
            // PV(diff)
            if(diff>1) ++ans;
            else if(diff==1){
                auto &v=in[i][j];
                if(vis[v]!=i) ++ans;
                else if(cnt[v]==0) ++ans;
            }
            // PV(ans)

            top=cd[j];
            while(top!=NULL) {
                --cnt[top->k];
                top=top->outr;
            }
        }
        top=del[i];
        while(top!=NULL){
            if(top->inl==NULL) ci[top->y1]=top->inr;
            else top->inl->inr=top->inr;
            if(top->inr!=NULL) top->inr->inl=top->inl;

            if(top->outl==NULL) cd[top->y2]=top->outr;
            else top->outl->outr=top->outr;
            if(top->outr!=NULL) top->outr->outl=top->outl;

            top=top->del;
        }
    }
    printf("%d\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
