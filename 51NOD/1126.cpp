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

const int maxn=1050;
int f[maxn],len;
std::set<P> s;
int a,b,n;

//WA*7 循环节不一定是从第一个开始，例如无限循环小数，从某一位开始出现循环节
int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d%d",&a,&b,&n);
	f[0]=f[1]=1;len=2;
	do{
		s.is(P(f[len-2],f[len-1]));
		f[len]=(a*f[len-1]+b*f[len-2])%7;
		f[len]=(f[len]+7)%7;
		++len;
	}while(!s.count(P(f[len-2],f[len-1])));
	--n;
	int beg=0;
	for(;beg<len;++beg) if(f[beg]==f[len-2]&&f[beg+1]==f[len-1]) break;
	len-=2;
	if(n<len) printf("%d\n",(f[n]+7)%7);
	else{
		n-=len;
		n%=(len-beg);
		printf("%d\n",(f[beg+n]+7)%7);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
