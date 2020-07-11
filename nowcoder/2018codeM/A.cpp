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

const int maxn=505;
std::regex REGEX_TIME("^(\\d{2}):(\\d{2}):(.*)$");
struct Lan{
	int h,m;
	double s;
	Lan(std::string str){
		std::smatch match;
		std::regex_match(str,match,REGEX_TIME);
		// PV(match[1])PV(match[2])PV(match[3])
		h=std::stoi(match[1]);
		m=std::stoi(match[2]);
		s=std::stod(match[3]);
		// PV(h)PV(m)PV(s)
	}
	Lan(){}
	bool operator<(const Lan &rhs)const{return h<rhs.h||h==rhs.h&&(m<rhs.m||m==rhs.m&&(s<rhs.s));}
	bool operator!=(const Lan &rhs)const{return (*this<rhs)||(rhs<*this);}
};
struct Que{
	int x,y,z;
	Lan time;
	bool operator<(const Que &rhs)const{return time<rhs.time;}
	void print(){
		printf("%d %d %d %d %d %f\n",x,y,z,time.h,time.m,time.s);
	}
};
std::vector<Que> in;
int n,m,k;
int sta[maxn][maxn];
int ans,max,now;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	cin>>n>>m>>k;
	// scanf("%d%d%d",&n,&m,&k);
	FOR(i,0,k){
		std::string s;
		int x,y,z;
		cin>>x>>y>>z>>s;
		Que t;
		t.x=x;t.y=y;t.z=z;t.time=Lan(s);
		in.pb(t);
	}
	std::sort(in.begin(),in.end());
	// FOR(I,0,k) in[I].print();
	FOR(i,0,in.size()){
		if(i&&in[i].time!=in[i-1].time){ 
			if(now>=max){max=now;ans=i-1;}
		}
		if(in[i].z==0){
			sta[in[i].x][in[i].y]++;
			if(sta[in[i].x][in[i].y]==1) ++now;
		}
		else {
			sta[in[i].x][in[i].y]--;
			if(sta[in[i].x][in[i].y]==0) --now;
		}
	}
	if(now>=max) ans=in.size()-1;
	// PV(max)PV(ans)
	memset(sta,0,sizeof(sta));
	For(i,0,ans){
		if(in[i].z==0){
			sta[in[i].x][in[i].y]++;
		}
		else sta[in[i].x][in[i].y]--;
	}
	For(i,1,n) {For(j,1,m) printf("%d",sta[i][j]>=1);puts("");}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
