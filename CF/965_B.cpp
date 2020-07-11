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
char a[110][110];
int b[110][110];
int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	freopen("out","w",stdout);
#endif // MengLan
    int n,k,t;
    cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>a[i];

    for(int i=0;i<n;i++){
        t=0;
        for(int j=0;j<n;j++){
            if(a[i][j]=='.')
                t++;
            else t=0;
            if(t==k){
                for(int l=j;l>=j-k+1;l--)
                    b[i][l]++;  
                t=0;
                j=j-k+1;
            }
        }
    }

    for(int j=0;j<n;j++){
        t=0;
        for(int i=0;i<n;i++){
            if(a[i][j]=='.')
                t++;
            else t=0;
            if(t==k){
                for(int l=i;l>=i-k+1;l--)
                    b[l][j]++;  
            t=0;
            i=i-k+1;
            }
        }
    } 
    int max=-1;
    int x,y;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(max<b[i][j]){
                max=b[i][j];
                x=i;
                y=j;
            }
    cout<<x+1<<' '<<y+1<<endl;   

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
