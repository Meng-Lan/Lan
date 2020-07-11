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
using std::string;
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



int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    std::ios::sync_with_stdio(0);
    int f;
    cin>>f;
    while(f){
        int n,m;
        cin>>n>>m;
        string s;
        cin>>s;
        int t[n/2+3],sum=0,k=0;
        memset(t,0,sizeof(t));
        if(n%2!=0){
           for(int i=0;i<=n/2;i++)
              if(s[n/2-i]!=s[n/2+i]){
                   t[n/2-i]=1;sum++;
               }
               while(m){
                   int x;char c;
                   cin>>x>>c;--x;
                   s[x]=c;
                if(x>=n/2)x=n-x-1;
                  // cout<<s[x]<<' '<<s[n-x-1]<<endl;
                    if(s[x]!=s[n-x-1])
                        if(t[x]!=1){
                           t[x]=1;sum++;}
                    if(s[x]==s[n-x-1]){
                        if(t[x]==1){
                            t[x]=0;sum--;}
                    }
                    if(sum==0) k++;
                    m--;
               }
           }
        if(n%2==0){
           for(int i=1;i<=n/2;i++)
             if(s[n/2-i]!=s[n/2+i-1]){
                   t[n/2-i]=1;sum++;//cout<<sum<<endl;
               }
               while(m){
                   int x;char c;
                   cin>>x>>c;x--;
                   s[x]=c;
                   if(x>=n/2)x=n-x-1;
                   //cout<<s[x]<<' '<<s[n-x-1];
                    if(s[x]!=s[n-x-1])
                        if(t[x]!=1){
                           t[x]=1;sum++;}
                    if(s[x]==s[n-x-1]){
                        if(t[x]==1){
                            t[x]=0;sum--;}
                    }
                    if(sum==0) k++;
                    m--;
               }
           }
           cout<<k<<endl;           
           f--;
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
