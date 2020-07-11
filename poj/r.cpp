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

#define RAND (rand()%500+1)
//RAND_MAX

int main(){
    srand(time(NULL));
    int T=RAND;
    printf("%d\n",T);
    while(T--){
        int n=RAND;
        int m=(1*RAND*RAND)%(n*n)+1;
        printf("%d %d\n",n,m);
    }
    return 0;
}