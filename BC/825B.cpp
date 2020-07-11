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
    int eof=0;
	inline char getchar() {
		static const int BUFSIZE=201314;
		static char buf[BUFSIZE],*begin,*end;
		if(begin==end) {
			begin=buf;
			end=buf+fread(buf,1,BUFSIZE,stdin);
			if(begin==end) return eof=-1;
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
#ifdef MengLan
#define RD(name)\
do{\
    IO::eof=scanf("%d",&name);\
}while(0)
#else
#define RD(name)\
do{\
    read(name);\
}while(0)
#endif

const int maxn=15e4+10;
const int maxq=1e6+10;
const int BEGIN=maxn+1;
const int END=maxn+2;
struct Node{
    int l,r,v,oth,idx;
    int& left(){
        if(oth) return r;
        else return l;
    }

    int& right(){
        if(oth) return l;
        return r;
    }
};
Node *bgn[maxn],*end[maxn],node[maxq];
int lan=0;
int n,q;

void link(Node &a,Node &b){
    a.right()=b.idx;
    b.left()=a.idx;
}

inline int getNode(){
    int idx=lan++;
    Node &it=node[idx];
    it.idx=idx;
    it.l=it.r=0;
    it.oth=0;
    it.v=-1;
    return idx;
}

void add(int u,int w,int val){
    int idx=getNode();
    node[idx].v=val;
    node[idx].oth=0;
    if(w==0){
        Node &a=*bgn[u],&b=node[a.right()];
        // PV(a.left())PV(a.right())
        // PV(b.left())PV(b.right())
        link(a,node[idx]);
        link(node[idx],b);
        
        // PV(a.left())PV(a.right())PV(idx)
        // PV(node[idx].left())PV(node[idx].right())
        // PV(b.left())PV(b.right())
    }
    else{
        Node &a=*end[u],&b=node[a.left()];
        link(b,node[idx]);
        link(node[idx],a);
    }
}

bool empty(int u){
    Node &a=*bgn[u];
    Node &b=node[a.right()];
    if(b.v==END) return true;
    return false;
}

int query(int u,int w){
    int ans=-1;
    if(empty(u)) return ans;
    if(w==0){
        Node &a=*bgn[u];
        Node &b=node[a.right()];
        Node &c=node[b.right()];
        ans=b.v;
        c.oth^=b.oth;
        link(a,c);
    }
    else{
        Node &a=*end[u];
        Node &b=node[a.left()];
        Node &c=node[b.left()];
        ans=b.v;
        c.oth^=b.oth;
        link(c,a);
    }
    return ans;
}

void link(int u,int v,int w){
    if(empty(v)) return;
    if(w==0){
        Node &a=*end[u];
        Node &b=node[a.left()];
        Node &c=*bgn[v];
        Node &d=node[c.right()];
        Node &e=*end[v];
        Node &f=node[e.left()];
        link(b,d);
        link(f,a);
        link(c,e);
    }
    else{
        Node &a=*end[u];
        Node &b=node[a.left()];
        Node &c=*bgn[v];
        Node &d=node[c.right()];
        Node &e=*end[v];
        Node &f=node[e.left()];
        d.oth^=1;
        f.oth^=1;
        link(b,f);
        link(d,a);
        link(c,e);
    }
}



int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int b=0;
    while(1){
        RD(n);RD(q);
        if(IO::eof==-1) break;
        lan=0;
        For(i,1,n){
            int idx=getNode();
            bgn[i]=&node[idx];
            node[idx].v=BEGIN;
            
            idx=getNode();
            end[i]=&node[idx];
            node[idx].v=END;
            link(*bgn[i],*end[i]);
        }
        b=lan;
        FOR(i,0,q){
            int cmd;RD(cmd);
            if(cmd==1){
                int u,w,val;
                RD(u);RD(w);RD(val);
                add(u,w,val);
            }
            else if(cmd==2){
                int u,w;
                RD(u);RD(w);
                int ans=query(u,w);
                printf("%d\n",ans);
            }
            else {
                int u,v,w;
                RD(u);RD(v);RD(w);
                link(u,v,w);
            }
            FOR(i,b,lan) printf("i:%d  v:%d l:%d r:%d o:%d\n",node[i].idx,node[i].v,node[i].left(),node[i].right(),node[i].oth);
        }
        For(i,1,n){
            bgn[i]=nullptr;
            end[i]=nullptr;
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}

/*
3 14
1 1 1 1
1 1 1 2
1 2 1 3
1 2 1 4
1 3 1 5
1 3 1 6
3 2 3 1
3 1 2 1
2 1 0
2 1 0
2 1 0
2 1 0
2 1 0
2 1 0
*/