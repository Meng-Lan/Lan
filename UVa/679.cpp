#include<iostream>
#include<cstdio>
#include<stack>
#include<cstring>
#include<sstream>
using namespace std;
int main() {
#ifdef MengLan
	//int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan
    int t;
    while(scanf("%d",&t)==1&&(t!=-1)){
        while(t--){    
            int d,c;
            int k=1;
            scanf("%d%d",&d,&c);
            for(int i=0;i<d-1;i++){
                if(c%2==0) {
                    k=k*2+1;c=c/2;}
                else {
                    k=k*2; c=(c+1)/2;
                }
            }
            printf("%d\n",k);
        }
    }
#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
