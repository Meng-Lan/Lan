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

struct problem{
    int trie,ac;
    std::string s;
    problem(int t,int a,std::string s):trie(t),ac(a),s(s){}
    problem():problem(0,0,std::string()){}
}p[35][35];

struct sub{
    int x,y;
    bool z;
    std::string s1;
}su[600005];

std::vector<P> v1;
int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    std::ios::sync_with_stdio(0);
    int T,n,m,k;
    cin>>T;
    while(T--){
        for(auto &i:p) for(auto &j:i) j=problem();
        cin>>n>>m>>k;
        for(int i=0;i<k;i++){
            cin>>su[i].x>>su[i].y>>su[i].z>>su[i].s1;
            p[su[i].y][su[i].x].trie++;
            if(su[i].z){
               p[su[i].y][su[i].x].ac++;
               p[su[i].y][su[i].x].s=su[i].s1;
            }
        }
        typedef std::pair<std::string,int> PSI;
        for(int i=1;i<=n;i++){
            std::vector<PSI> v;
            for(int j=1;j<=m;++j) if(p[j][i].ac){
                v.push_back(PSI(p[j][i].s,j));
            }
            std::sort(v.begin(),v.end());
            if(v.empty()) cout<<"-1";
            else cout<<v[0].second;
            if(i!=n) cout<<" ";
            else cout<<endl;
        }
        std::vector<PSI> v;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                if(p[j][i].ac)
                    v.push_back(PSI(p[j][i].s,j));
        }
        //std::sort(std::begin(v),std::end(v));
        std::sort(v.begin(),v.end());
        cout<<v[0].second<<" ";
        cout<<v[v.size()-1].second<<" ";
        
        v1.clear(); 
        for(int i=1;i<=m;++i){
            int cnt=0;
            for(int j=1;j<=n;++j) if(p[i][j].ac&&p[i][j].trie==1) ++cnt;
            v1.push_back(P(cnt,i));
        }
        std::sort(v1.begin(),v1.end(),[](P &x,P &y){return x.fi>y.fi||x.fi==y.fi&&x.se<y.se;});
        cout<<v1[0].se<<" ";
        v1.clear();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                if(p[j][i].ac)
                    v1.push_back(P(p[j][i].trie,j));
        }
        std::sort(v1.begin(),v1.end(),[](P &x,P &y){return x.fi>y.fi||x.fi==y.fi&&x.se<y.se;});
        cout<<v1[0].second<<endl;
    }


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
