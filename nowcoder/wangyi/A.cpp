#include<iostream>
#include<cstdio>
const int maxn=1e3+10;
char s[maxn];
int T,n;

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d %s",&n,s);
        int ans=0;
        int i=0;
        while(i<n){
            if(s[i]=='.'){++ans;i+=3;}
            else ++i;
        }
        printf("%d\n",ans);
    }
    return 0;
}