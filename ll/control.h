#pragma once
#include<bits/stdc++.h>
extern "C"{
    #include <sys/epoll.h>
}

namespace control{
    extern int now_epoll_act_cnt;
    extern int now_listen_sz;
    extern int now_connection_sz;
    extern int handle_conn_sz;
    extern int handle_close_sz;
    extern std::vector<struct epoll_event> now_epoll_act;
}