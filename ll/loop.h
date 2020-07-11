#pragma once
#include"event.h"
#include"epoll.h"
#include<bits/stdc++.h>
#include"spin.h"
#include"listener.h"

class ll_loop{
    public:

    ll_epoll epoll;
    std::vector<ll_event*> events;
    std::vector<VCallback> todo_functor;
    bool started;
    // int chk;
    bool quit;
    std::thread::id thread_id;
    ll_spin spin;

    ll_loop();
    ~ll_loop();

    void loop();
        
    void update_event(ll_event *event);

    bool is_in_loop_thread(){return thread_id==std::this_thread::get_id();}

    void run_in_loop(VCallback cb);
};