#include<iostream>
#include<cstdio>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
const int maxn = 1e5 + 10;
int num[maxn << 2];
void pushUP(int rt){
