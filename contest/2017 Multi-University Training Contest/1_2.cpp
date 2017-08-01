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
#define mp std::make_pair
ll Factorial(ll i) { return i > 1?i*Factorial(i-1):1; }
ll Combination(ll n,ll r) {
	if(n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for(ll i=n-r+1; i<=n; ++i) ansn*=i;
	for(ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if(!vis[i]) for(int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if(!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if(!phi[i])
		for(int j=i; j<=n; j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int sigma=26;
const int maxn=1e5+10;
const int mod=1e9+7;
int n,ch[sigma][maxn],bad[sigma];
char s[maxn];

struct Node {
	char c;
	std::vector<int> v;
	int num;
	bool vis;
	bool operator<(const Node &rhs)const {
		if(v.size()!=rhs.v.size()) return v.size()>rhs.v.size();
		return v>rhs.v;
	}
	ll sum() {
		ll ans=0;
		for(auto &t:v) {
			ans*=sigma;
			ans+=(ll)t*num;
			ans%=mod;
		}
		return ans;
	}
}ans[sigma];

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%d",&n)==1&&n) {
		memset(bad,0,sizeof(bad));
		memset(ch,0,sizeof(ch));
		int mlen=0;
		FOR(i,0,n) {
			scanf("%s",s);
			int len=strlen(s);
			mlen=std::max(len,mlen);
			bad[s[0]-'a']=1;
			FOR(j,0,len) {
				ch[s[j]-'a'][len-j]++;
			}
		}
		mlen+=5;
		FOR(i,0,sigma) {
			For(j,1,mlen) if(ch[i][j]) {
				ch[i][0]=j;
				ch[i][j+1]+=ch[i][j]/sigma;
				ch[i][j]%=sigma;
			}
			std::reverse(ch[i]+1,ch[i]+ch[i][0]+1);
			ans[i].v.assign(ch[i]+1,ch[i]+ch[i][0]+1);
			ans[i].c=i;
			ans[i].num=-1;
			ans[i].vis=bad[i];
		}
		std::sort(ans,ans+sigma);
		int j=25;
		FOR(i,0,sigma) if(ans[i].v.size()) ans[i].num=j--;
		bool add=false;
		int zero=-1;
		FOR(i,0,sigma) if(ans[i].v.size()&&ans[i].vis&&ans[i].num==0) { add=true;break; }
		if(add) for(int i=25;i>=0;--i) if(ans[i].v.size()&&!ans[i].vis) { zero=i;break; }
		ll res=0;
		FOR(i,0,sigma) if(i!=zero&&ans[i].v.size()){
			//printf("c:%c num:%d vis:%d\n",ans[i].c+'a',ans[i].num,ans[i].vis);
			//for(auto &t:ans[i].v) printf("%d ",t);puts("");
			if(add&&ans[i].vis&&ans[i].num<ans[zero].num) ans[i].num++;
			res+=ans[i].sum();res%=mod;
		}
		printf("Case #%d: %lld\n",++kase,res);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}