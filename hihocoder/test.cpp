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

const int maxn=20;
int q[maxn];
int p[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    For(n,1,10){
        FOR(i,0,3) q[i]=i+1;
        do{
            int a=q[0]-q[1],b=q[0]-q[2],c=q[1]-q[2];
            ll ans=0;
            FOR(i,0,n) p[i]=i+1;
            do{
                int cnt=0,tcnt=0;
                FOR(i,0,n-2) FOR(j,i+1,n-1) FOR(k,j+1,n){
                    int a2=p[i]-p[j];
                    int b2=p[i]-p[k];
                    int c2=p[j]-p[k];
                    ++cnt;
                    if(!(a*a2>0&&b*b2>0&&c*c2>0)) ++tcnt;
                }
                if(cnt==tcnt) ++ans;
            }while(std::next_permutation(p,p+n));
            PA(q,0,3);PA(p,0,n);PV(ans);
        }while(std::next_permutation(q,q+3));
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
