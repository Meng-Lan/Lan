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
inline void read(char *s){
    int c;
    while(isspace(c=IO::getchar()));
    int idx=0;
    s[idx++]=c;
    while(isalpha(c=IO::getchar())){ s[idx++]=c;}
    s[idx]='\0';
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int maxn=1e5+10;
std::map<std::string,int> m;
int n;
char s[100];

int getmin(char *s,int len){
    int i=0,j=1,k=0;
    while(i<len&&j<len&&k<len){
        int t=s[(i+k)%len]-s[(j+k)%len];
        if (!t) k++;
        else{
            if (t>0) i+=k+1;
            else j+=k+1;
            if (i==j) j++;
            k=0;
        }
    }
    return std::min(i,j);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T=read();//scanf("%d",&T);
    while(T--){
        // scanf("%d",&n);
        read(n);
        m.clear();
        FOR(i,0,n){
            // scanf("%s",s);
            read(s);
            int len=strlen(s);
            int min=getmin(s,len);
            memcpy(s+len,s,len);
            std::string t(s+min,s+min+len);
            std::reverse(s,s+len+len);
            min=getmin(s,len);
            std::string tmp(s+min,s+min+len);
            if(t==tmp) m[t]++;
            else {m[t]++;m[tmp]++;}
        }
        bool ans=false;
        for(auto &v:m) if(v.second>1) {ans=true;break;}
        printf("%s\n",ans?"Yeah":"Sad");
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
