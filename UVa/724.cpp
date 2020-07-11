#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n,p[10];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&p[i]);
    sort( p,p+n);
    do{
        for(int i=0;i<n;i++) printf("%d",p[i]);
        printf("\n");
    }while(next_permutation(p,p+n));
    system("pause");
    return 0;
}