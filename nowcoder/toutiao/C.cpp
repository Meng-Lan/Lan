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

char s[111];
int cnt,len;

ll getll(){
	ll num=0;
	while(cnt<len&&isdigit(s[cnt])){
		num*=10;num+=s[cnt]-'0';++cnt;
	}
	return num;
}

char getc(){
	return s[cnt++];
}

char cc[11][11][11]={
	{"66666","6...6","6...6","6...6","66666"},
	{"....6","....6","....6","....6","....6"},
	{"66666","....6","66666","6....","66666"},
	{"66666","....6","66666","....6","66666"},
	{"6...6","6...6","66666","....6","....6"},
	{"66666","6....","66666","....6","66666"},
	{"66666","6....","66666","6...6","66666"},
	{"66666","....6","....6","....6","....6"},
	{"66666","6...6","66666","6...6","66666"},
	{"66666","6...6","66666","....6","66666"},
};

int p[111];

void pt(){printf("..");}
void pt(int n,int x){
	printf("%s",cc[n][x]);
}

void print(ll res){
	int len=0;
	if(res==0) p[len++]=0;
	else{
		while(res){
			p[len++]=res%10;res/=10;
		}
		std::reverse(p,p+len);
	}
	FOR(i,0,5) FOR(j,0,len){
		if(j) pt();
		pt(p[j],i);
		if(j==len-1) printf("\n");
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
		scanf(" %s",s);
		std::stack<ll> sl;
		std::stack<char> sc;
		cnt=0;len=strlen(s);
		sl.push(getll());
		while(cnt<len){
			char c=getc();
			ll num=getll();
			if(c=='*'){
				ll a=sl.top();sl.pop();
				sl.push(a*num);
			}
			else{
				sl.push(num);sc.push(c);
			}
		}
		while(!sc.empty()){
			ll a=sl.top();sl.pop();
			ll b=sl.top();sl.pop();
			char c=sc.top();sc.pop();
			if(c=='+') sl.push(b+a);
			else sl.push(b-a);
		}
		print(sl.top());
	}



#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
