#pragma once
#include"threadpool.h"
#include"tcp_connection.h"
#include"connector.h"
#include"spin.h"

class ll_tcp_server{
    public:

    ll_thread_pool threadpool;
    typedef std::shared_ptr<ll_connector> connector_ptr;
    std::vector<connector_ptr> connections;
    ll_spin spin;

    ll_tcp_server(int threadnum):threadpool(threadnum){}
    ll_tcp_server():ll_tcp_server(1){}
    ~ll_tcp_server(){}

    void listen(int port,connection_callback &conn_cb){
        threadpool.listen(port,conn_cb);
    }
    
    void start(){threadpool.start();}

    int connect(char *ipaddr,int port,connection_callback &conn_cb){
        ll_loop *loop=threadpool.get_next_loop();
        connector_ptr conn(new ll_connector(loop,ipaddr,port,conn_cb));
        {
            ll_spin_guard gurad(ll_spin);
            connections.push_back(conn);
        }
        return conn->connector_id;
    };
};