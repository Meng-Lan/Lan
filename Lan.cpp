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

void print(std::vector<P> &in){
	for(auto &v:in) printf("(%d,%d) ",v.fi,v.se);
	puts("");
}

bool isconn(P &l,P &r){
	return l.fi==r.fi||l.se==r.se;
}

struct Line{
	int h,x,k;
	Line(int h,int x,int k):h(h),x(x),k(k){}
	Line():Line(0,0,0){}
	bool operator<(const Line &rhs){
		if(x!=rhs.x) return x<rhs.x;
		if(k!=rhs.k) return k<rhs.k;
		if(k==1) return h>rhs.h;
		if(k==2) return h<rhs.h;
	}
	void print(){
		printf("h:%d x:%d k:%d\n",h,x,k);
	}
};

std::vector<P> merge(std::vector<P> l,std::vector<P> r){
	puts("\n");
	std::vector<Line> line;
	for(int i=0;i<l.size();i+=2){
		if(l[i].se<l[i+1].se) {
			line.pb({l[i+1].se,l[i].fi,1});
			// line.pb({0,l[i].fi,2});//
		}
		else {
			line.pb({l[i].se,l[i].fi,2});
		}
	}
	for(int i=0;i<r.size();i+=2){
		if(r[i].se<r[i+1].se) line.pb({r[i+1].se,r[i].fi,1});
		else line.pb({r[i].se,r[i].fi,2});
	}
	std::sort(line.begin(),line.end());
	std::multiset<int> s;
	std::vector<P> ret;
	s.insert(0);
	for(int i=0;i<line.size();++i){
		// printf("h=%d x=%d k=%d\n",line[i].h,line[i].x,line[i].k);
		int mx=*s.rbegin();
		PV(s.size());
		line[i].print();
		if(line[i].k==1){
			if(line[i].h<=mx) s.insert(line[i].h);
			else{
				ret.pb({line[i].x,mx});
				ret.pb({line[i].x,line[i].h});
				s.insert(line[i].h);
			}
		}
		if(line[i].k==2){
			if(line[i].h==mx&&s.count(mx)==1){
				s.erase(mx);
				ret.pb({line[i].x,line[i].h});
				ret.pb({line[i].x,*s.rbegin()});
			}
			else s.erase(s.find(line[i].h));
		}
	}
	return ret;
}

std::vector<P> unio(std::vector<std::vector<P>> in){
	if(in.size()==0) return std::vector<P>();
	else if(in.size()==1) return in[0];
	else if(in.size()==2){
		auto l=in[0],r=in[1];
		auto ret=merge(l,r);
		return ret;
	}
	std::vector<P> left;
	for(int i=0;i<in.size()/2;++i) for(int j=0;j<in[i].size();++j) left.pb(in[i][j]);
	std::vector<P> right;
	for(int i=in.size()/2;i<in.size();++i) for(int j=0;j<in[i].size();++j) right.pb(in[i][j]);
	return merge(left,right);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	// std::vector<P> l={{2,0},{2,2},{7,2},{7,0}},r={{4,0},{4,3},{9,3},{9,0}};
	// print(l);
	// print(r);
	// auto res=merge(l,r);
	// print(res);
	std::vector<std::vector<P>> in={
		{{2,0},{2,2},{7,2},{7,0}},
		{{4,0},{4,3},{9,3},{9,0}},
		{{13,0},{13,2},{18,2},{18,0}},
		{{18,0},{18,4},{25,4},{25,0}},
		{{22,0},{22,3},{40,3},{40,0}}
	};
	auto res=unio(in);
	print(res);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
