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

    int x,y;
    char s[100];

    int ctoi(char c){
        if(isdigit(c)) return c-'0';
        return c-'A'+10;
    }

    int main() {
    #ifdef MengLan
        int Beginning=clock();
        //freopen("in","r",stdin);
        //freopen("out","w",stdout);
    #endif // MengLan

        int T;scanf("%d",&T);
        while(T--){
            scanf("%d%d%s",&x,&y,s);
            int len=strlen(s);
            FOR(i,1,len){
                ll tx=0;
                FOR(j,0,i) {tx*=x;tx+=ctoi(s[j]);}
                ll ty=0;
                FOR(j,i,len) {ty*=y;ty+=ctoi(s[j]);}
                if(tx==ty){printf("%lld\n",tx);break;}
            }
        }

    #ifdef MengLan
        printf("Time: %d\n",clock()-Beginning);
        system("pause");
    #endif // MengLan
        return 0;
    }
