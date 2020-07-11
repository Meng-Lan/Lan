#include<bits/stdc++.h>
using namespace std;
const int maxn=100+5;
int n;
double m[maxn*2];
struct building{
    int id,x,y,w,d,h;
}b[maxn];
bool cmp(building a,building b){
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}
bool visible(int i,double mx){
    if(!(b[i].x<=mx&&b[i].x+b[i].w>=mx))
        return false;
    for(int k=0;k<n;k++)
        if(b[k].y<b[i].y&&b[k].h>=b[i].h&&b[k].x<=mx&&b[k].x+b[k].w>=mx)
            return false;
    return true;
}
int main(){
    int kase=0;
    while(cin>>n&&n){
        for(int i=0;i<n;i++){
            cin>>b[i].x>>b[i].y>>b[i].w>>b[i].d>>b[i].h;
            m[i*2]=b[i].x;
            m[i*2+1]=b[i].x+b[i].w;
            b[i].id=i+1;
        }
        sort(b,b+n,cmp);
        sort(m,m+n*2);
        int a=unique(m,m+n*2)-m;
        if(kase++)
            cout<<endl;
        cout<<"For map #"<<kase<<", the visible buildings are numbered as follows:"<<endl<<b[0].id;
        for(int i=1;i<n;i++){
            bool vis=false;
            for(int j=0;j<a-1;j++)
                if(visible(i,(m[j]+m[j+1])/2)){
                    vis=true;break;
                }
            if(vis)
                cout<<" "<<b[i].id;
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}
