#pragma once
#include"event.h"


class ll_loop;
class ll_tcp_connection;
class ll_listener{
    public:
    
    ll_loop *loop;
    int fd;
    ll_event event;
    connection_callback conn_cb;
    std::map<int,tcp_connection_ptr> connections;

    ll_listener(ll_loop *loop,int port);

    ~ll_listener(){
        ::close(fd);
    }

    void listen();

    void handle_read();

    void new_connection(int fd,const struct sockaddr &addr);

    void destory_connection(int fd);

    void erase_connection(int fd);
};