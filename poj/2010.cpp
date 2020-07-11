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

const int maxn=1e5+10;
int n,c,f;
struct Lan{
    int src,cost;
    Lan(int src=0,int cost=0):src(src),cost(cost){}
    bool operator<(const Lan &rhs)const{
        return src>rhs.src||src==rhs.src&&cost<rhs.cost;
    }
};
struct Node{
    int src,cost;
    Node(int src=0,int cost=0):src(src),cost(cost){}
    bool operator<(const Node &rhs)const{
        return cost<rhs.cost||cost==rhs.cost&&src<rhs.src;
    }
}in[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d",&n,&c,&f);
    FOR(i,0,c) scanf("%d%d",&in[i].src,&in[i].cost);
    std::sort(in,in+c);
    //FOR(i,0,c) printf("src:%d cost:%d\n",in[i].src,in[i].cost);
    int ls=(n>>1),rs=n-ls;
    //PV(ls);PV(rs);
    std::priority_queue<Lan> max;
    std::priority_queue<Node> min;
    FOR(i,0,c){
        if(max.size()<rs){max.push(Lan(in[i].src,in[i].cost));f-=in[i].cost;}
        else if(min.size()<ls){
            max.push(Lan(in[i].src,in[i].cost));f-=in[i].cost;
            Lan x=max.top();max.pop();
            min.push(Node(x.src,x.cost));
        }
        else if(in[i].src>max.top().src){
            Lan x=max.top();
            min.push(Node(x.src,x.cost));
            Node y=min.top();
            if(f-in[i].cost+y.cost<0) break;
            f=f-in[i].cost+y.cost;
            max.push(Lan(in[i].src,in[i].cost));
            max.pop();min.pop();
        }
        //PV(f);PV(max.size());PV(min.size());
    }
    if(f<0) printf("-1\n");
    else printf("%d\n",max.top().src);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
