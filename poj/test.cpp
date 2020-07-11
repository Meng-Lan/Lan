#include <cstdio>  
#include <iostream>  
using namespace std;  
long long const INF=0x3f3f3f3f3f3f3f;  
long long N;  
long long cal(long long i,long long j){  
    return i*i+100000*i+j*j-100000*j+i*j;  
}  
long long judge(long long d){  
    long long j,l,r,mid,ans,sum;  
    sum=ans=0;  
    for(j=1;j<=N;j++){  
        l=1,r=N;  
        while(l<=r){  
            mid=(l+r)/2;  
            if(cal(mid,j)<=d){  
                ans=mid;  
                l=mid+1;  
            }  
            else  
            r=mid-1;  
        }  
        sum+=ans;  
    }                           //因为这个函数是关于i递增的，因此二分有多少  
    return sum;                 //个值大于d  
}  
int main(){  
    long long i,j,l,r,t,M,mid,ans;  
    scanf("%I64d",&t);  
    while(t--){  
        scanf("%I64d%I64d",&N,&M);  
        l=-1*INF,r=INF;         //二分函数值，这个值可能特别大，因此上下限  
        while(l<=r){            //要设的足够大      
            mid=(l+r)/2;  
            if(judge(mid)>=M){  
                ans=mid;  
                r=mid-1;  
            }  
            else  
            l=mid+1;  
        }  
//            cout<<"dfasfasd"<<endl;  
        printf("%I64d\n",ans);  
    }  
    return 0;  
}  