#include"loop.h"
#include"control.h"


ll_loop::ll_loop():started(false),quit(false),thread_id(std::this_thread::get_id()){}

ll_loop::~ll_loop(){}

void ll_loop::loop(){
    started=true;
    quit=false;
    // DBX(thread_id);
    while(!quit){
        epoll.poll(events);
        for(auto &v:events){
            v->handle();
        }
        std::vector<VCallback> temp_functor;
        {
            ll_spin_guard gurad(spin);
            temp_functor.swap(todo_functor);
        }

        for(auto &f:temp_functor) f();
    }
}

void ll_loop::update_event(ll_event *event){
    if(is_in_loop_thread()) epoll.update_event(event);
    else run_in_loop(std::bind(&ll_epoll::update_event,&epoll,event));
}

void ll_loop::run_in_loop(VCallback cb){
    ll_spin_guard guard(spin);
    todo_functor.push_back(cb);
}