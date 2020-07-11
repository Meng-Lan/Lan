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

std::string s;
int in[3],n;

int replace(char &v,int sta){
    int num=v-'0';
    if(sta==1&&in[num]>0){
        FOR(i,0,num) if(in[i]<0) {--in[num];++in[i];return i+'0';}
    }
    if(sta==2&&in[num]>0){
        for(int i=2;i>=0;--i) if(in[i]<0) {--in[num];++in[i];return i+'0';}
    }
    return v;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    cin>>n>>s;
    FOR(i,0,s.size()) in[s[i]-'0']++;
    FOR(i,0,3) in[i]-=n/3;
    for(auto &v:s) v=replace(v,1);
    for(int i=s.size()-1;i>=0;--i) s[i]=replace(s[i],2);
    cout<<s<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}