#pragma once
#include"loop_thread.h"

class ll_thread_pool{
    public:

    int thread_cnt;
    std::vector<std::unique_ptr<ll_loop_thread>> threads;
    std::vector<ll_loop*> loops;
    bool started;
    int cur_id;

    ll_thread_pool(int thread_cnt):thread_cnt(thread_cnt),started(false),cur_id(0){assert(thread_cnt>=1);}
    ~ll_thread_pool(){}

    void start(){
        assert(started==false);

        started=true;

        for(int i=0;i<thread_cnt;++i){
            ll_loop_thread *p=new ll_loop_thread();
            threads.push_back(std::unique_ptr<ll_loop_thread>(p));
            loops.push_back(p->start());
        }

        // cout<<"thread_poll started finish"<<endl;
    }

    void listen(int port,connection_callback &conn_cb){
        if(started==false) start();
        for(auto &v:threads) v->listen(port,conn_cb);        
    }

    ll_loop* get_next_loop(){
        assert(loops.size()>0);
        ll_loop *loop=loops[cur_id];
        cur_id=(cur_id+1)%loops.size();
        return loop;
    }
};