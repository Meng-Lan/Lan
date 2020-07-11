#pragma once
#include"type.h"
#include"event.h"
#include"listener.h"

class ll_loop;
class ll_event;
class ll_tcp_connection{
    public:

    ll_loop *loop;
    int fd;
    ll_event event;
    struct sockaddr addr;
    int state;
    Vtcp_connection_callback connection_cb;
    V3_tcp_connection_callback read_cb;
    Vtcp_connection_callback write_cb;
    Vtcp_connection_callback close_cb;
    std::function<void(int)> destory_cb;

    static const int connecting=0;
    static const int connected=1;
    static const int disconnection=2;

    ll_tcp_connection(ll_loop *loop,int fd,const struct sockaddr &addr);
    ~ll_tcp_connection();

    void connect_established();

    void handle_read();

    void handle_close();

    void handle_error();

    void send(std::shared_ptr<char> ptr,int len);

    void send_in_loop(std::shared_ptr<char> ptr,int len);

};