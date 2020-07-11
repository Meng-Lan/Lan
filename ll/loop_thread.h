#pragma once

#include"loop.h"
// #include"spin.h"

class ll_loop_thread{
    public:

    ll_loop *loop;
    std::thread thread;
    // ll_spin spin;
    typedef std::shared_ptr<ll_listener> ll_listener_ptr;
    std::map<int,ll_listener_ptr> listeners;

    ll_loop_thread():loop(NULL),thread(std::bind(&ll_loop_thread::thread_func,this)){}
    ~ll_loop_thread(){listeners.clear();}

    void thread_func(){
        ll_loop _loop;
        loop=&_loop;
        _loop.loop();

        cout<<"loop stop"<<endl;
    }

    ll_loop* start(){
        while(loop==NULL);
        return loop;
    }

    void listen(int port,connection_callback &conn_cb){
        ll_listener_ptr listen_ptr(new ll_listener(loop,port));
        listen_ptr->conn_cb=conn_cb;
        listeners[port]=listen_ptr;
        listen_ptr->listen();
    }
};