#pragma once
#include"type.h"
#include"spin.h"

class ll_loop;
class ll_connector{
    public:

    ll_loop *loop;
    const int fd;
    tcp_connection_ptr connection;
    std::string ip;
    int port;
    int try_cnt;
    connection_callback conn_cb;
    int connector_id;
    static int connector_num;
    static ll_spin spin;

    ll_connector(ll_loop *loop,char *ipaddr,int port,connection_callback &conn);
    ~ll_connector();

    void new_connection(int fd,struct sockaddr_in &addr);
    void destory_connection(int);
    void erase_connection(int);
    void retry();
};