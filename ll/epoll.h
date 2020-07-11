#pragma once
extern "C"{
    #include <sys/epoll.h>
    #include<errno.h>
}
#include"event.h"

namespace{
    const int sNew=0,sAdd=1,sDelete=2;
}

class ll_epoll{
    public:

    std::vector<struct epoll_event> temp_events;
    int epfd;

    static const int init_size=32;
    static const int timeout=1e3;

    ll_epoll():epfd(::epoll_create1(EPOLL_CLOEXEC)),temp_events(init_size){}
    ~ll_epoll(){::close(epfd);}

    void poll(std::vector<ll_event*> &events);

    void update_event(ll_event *event);

    private:

    void update(ui op,ll_event *event){
        event->event.data.ptr=event;
        const int &fd=event->fd;
        int ret=::epoll_ctl(epfd,op,fd,&event->event);
        ASS(ret!=-1);
    }
};