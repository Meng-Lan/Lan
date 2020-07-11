#pragma once
extern "C"{
#include <sys/epoll.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
}
#include<bits/stdc++.h>

typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
using std::cin;
using std::cout;
using std::endl;

typedef std::function<void()> VCallback;
typedef std::function<void(int ,const struct sockaddr&)> NewConnectionCallback;
class ll_tcp_connection;
typedef std::shared_ptr<ll_tcp_connection> tcp_connection_ptr;
typedef std::function<void(ll_tcp_connection*)> Vtcp_connection_callback;
typedef std::function<void(ll_tcp_connection*,std::shared_ptr<char>,int)> V3_tcp_connection_callback;
struct connection_callback{
    Vtcp_connection_callback connection_cb;
    V3_tcp_connection_callback read_cb;
    Vtcp_connection_callback write_cb;
    Vtcp_connection_callback close_cb;

    // connection_callback():connection_cb(nullptr),
    bool empty(){return !(connection_cb||read_cb||write_cb||close_cb);}
};

#ifdef DEBUG
#define DB do{\
cout<<"file: "<<__FILE__<<" line: "<<__LINE__<<" function: "<<__FUNCTION__<<"\n";\
}while(0);
#define PV(name) cout<<#name"="<<name<<'\n';
#define DBX(x) do{\
cout<<"file: "<<__FILE__<<" line: "<<__LINE__<<" function: "<<__FUNCTION__<<" "#x"="<<x<<"\n";\
}while(0);
#define ASS(x) do{\
bool CHK=(x);\
if(!CHK) {\
    cout<<"file: "<<__FILE__<<" line: "<<__LINE__<<" function: "<<__FUNCTION__<<" ";\
    cout<<#x"="<<CHK<<" errno="<<errno<<"\n";\
    assert(CHK);\
}\
}while(0);



#else
#define DB  
#define PV(name)
#define DBX(x) 
#define ASS(x) do{bool chk=(x);}while(0);
#endif

