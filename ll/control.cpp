#include"control.h"

namespace control{
    int now_epoll_act_cnt=0;
    int now_listen_sz=0;
    int now_connection_sz=0;
    int handle_conn_sz=0;
    int handle_close_sz=0;
    std::vector<struct epoll_event> now_epoll_act;
}