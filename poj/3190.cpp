#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> P;
#define FOR(i, init, len) for (int i = (init); i < (len); ++i)
#define For(i, init, len) for (int i = (init); i <= (len); ++i)
#define fi first
#define se second
#define pb push_back
#define is insert
namespace IO
{
inline char getchar()
{
    static const int BUFSIZE = 5201314;
    static char buf[BUFSIZE], *begin, *end;
    if (begin == end)
    {
        begin = buf;
        end = buf + fread(buf, 1, BUFSIZE, stdin);
        if (begin == end)
            return -1;
    }
    return *begin++;
}
}
inline void read(int &in)
{
    int c, symbol = 1;
    while (isspace(c = IO::getchar()))
        ;
    if (c == '-')
    {
        in = 0;
        symbol = -1;
    }
    else
        in = c - '0';
    while (isdigit(c = IO::getchar()))
    {
        in *= 10;
        in += c - '0';
    }
    in *= symbol;
}
inline int read()
{
    static int x;
    read(x);
    return x;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
#define PA(name, init, len)                    \
    cout << #name "[" << (len - init) << "]="; \
    FOR(_, init, len)                          \
        cout << name[_] << " \n"[_ == (len - 1)];
#define Pa(name, init, len)                        \
    cout << #name "[" << (len - init + 1) << "]="; \
    For(_, init, len) cout << name[_] << " \n"[_ == (len)];
#define PV(name) cout << #name "=" << name << '\n';

const int maxn = 5e4 + 10;
struct Lan{
    int x, y, id;
    void input(){
        scanf("%d%d", &x, &y);
    }
    bool operator<(const Lan &rhs)const {
        return x<rhs.x||x==rhs.x&&y<rhs.y;
    }
} in[maxn];
int ans[maxn];
int n;
int main()
{
#ifdef MengLan
    int Beginning = clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    scanf("%d", &n);
    FOR(i,0,n) in[i].input(),in[i].id=i;
    std::sort(in,in+n);
    std::priority_queue<P,std::vector<P>,std::greater<P>> q;
    int cnt=0;
    FOR(i,0,n){
        if(q.empty()||(!q.empty()&&q.top().fi>=in[i].x)){
            q.push(P(in[i].y,++cnt));
            ans[in[i].id]=cnt;
        }
        else{
            P x=q.top();q.pop();
            q.push(P(in[i].y,x.se));
            ans[in[i].id]=x.se;
        }
    }
    printf("%d\n",cnt);
    FOR(i,0,n) printf("%d\n",ans[i]);


#ifdef MengLan
    printf("Time: %d\n", clock() - Beginning);
    system("pause");
#endif // MengLan
    return 0;
}
