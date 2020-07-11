#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
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
int min[maxn<<2],add[maxn<<2];
int ss[maxn];
char s[maxn];
int n,m;

inline void push(int rt){
    if(add[rt]){
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        add[rt]=0;
    }
}

inline void maintain(int rt){
    min[rt]=std::min(min[rt<<1]+add[rt<<1],min[rt<<1|1]+add[rt<<1|1]);
}

void build(int rt,int l,int r){
    if(l==r){min[rt]=ss[l];add[rt]=0;return;}
    int m=l+(r-l)/2;
    build(rt<<1,l,m);
    build(rt<<1|1,m+1,r);
    maintain(rt);
    add[rt]=0;
}

void update(int rt,int l,int r,int L,int R,int v){
    if(L<=l&r<=R){add[rt]+=v;return;}
    int m=l+(r-l)/2;
    if(L<=m) update(rt<<1,l,m,L,R,v);
    if(R>m) update(rt<<1|1,m+1,r,L,R,v);
    maintain(rt);
}

int query(int rt,int l,int r,int x){
    if(l==r) return min[rt]+add[rt];
    int m=l+(r-l)/2;
    push(rt);
    maintain(rt);
    if(x<=m) return query(rt<<1,l,m,x);
    return query(rt<<1|1,m+1,r,x);
}

int queryL(int rt,int l,int r,int x,int y){
    if(min[rt]+add[rt]>=y||x>r) return -1;
    if(l==r) return l;
    int m=l+(r-l)/2;
    push(rt);
    maintain(rt);
    int pos=-1;
    if(x<=m) pos=queryL(rt<<1,l,m,x,y);
    if(pos==-1) pos=queryL(rt<<1|1,m+1,r,x,y);
    return pos;
}

int queryR(int rt,int l,int r,int x,int y){
    if(min[rt]+add[rt]>y||x>r) return -1;
    if(l==r) return l;
    push(rt);
    maintain(rt);
    int m=l+(r-l)/2;
    int pos=queryR(rt<<1|1,m+1,r,x,y);
    if(pos==-1) pos=queryR(rt<<1,l,m,x,y);
    return pos;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        scanf("%s",s+1);
        ss[0]=0;
        For(i,1,n){int v=(s[i]=='('?1:-1);ss[i]=ss[i-1]+v;}
        //Pa(ss,0,n);
        build(1,0,n);
        FOR(i,0,m){
            int x,y;scanf("%d%d",&x,&y);
            if(x==1){
                int v=0;
                if(s[y]=='(') s[y]=')',v=-2;
                else s[y]='(',v=2;
                update(1,0,n,y,n,v);
            }
            else{
                int v=query(1,0,n,y-1);
                //PV(v);
                int pos=queryL(1,0,n,y,v);
                if(pos!=-1) printf("%d\n",pos-y);
                else {
                    pos=queryR(1,0,n,y,v);
                    if(pos!=-1) printf("%d\n",pos-y+1);
                    else puts("0");
                }
                //PV(pos)PV(op);
            }
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
