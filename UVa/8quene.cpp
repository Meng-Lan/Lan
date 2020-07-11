#include<bits/stdc++.h>
using namespace std;
int n,tot=0,vis[3][30],C[15];
void search(int cur){
    if(cur==n){
        tot++;
        if(tot<=3){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++)
                    if(j==C[i])
                        cout<<"1"<<" ";
                    else
                        cout<<"0"<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
    }
    else    
        for(int i=0;i<n;i++){
            if(!vis[0][i]&&!vis[1][cur+i]&&!vis[2][cur-i+n]){
                C[cur]=i;
                vis[0][i]=vis[1][cur+i]=vis[2][cur-i+n]=1;
                search(cur+1);
                vis[0][i]=vis[1][cur+i]=vis[2][cur-i+n]=0;
            }
        }
}
int main(){
    cin>>n;
    search(0);
    cout<<tot<<endl;
    system("pause");
    return 0;
}
