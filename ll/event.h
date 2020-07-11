#pragma once
extern "C"{
    #include <sys/epoll.h>
}
#include"type.h"


class ll_loop;
class ll_event{
    public:
    
    ll_loop *loop;
    struct epoll_event event;
    ui revents;
    int fd;
    VCallback read_cb,write_cb,close_cb,error_cb;
    int state;

    ll_event(ll_loop *loop,int fd);
    ~ll_event(){}

    void update();
    //void remove(){}

    #define CHKE do{\
    if(event.events>=256){DBX(event.events)}\
    }while(0);

    void enable_read(){event.events|=ReadEvent;CHKE update();}
    void disable_read(){event.events&=~ReadEvent;CHKE update();}
    void enable_write(){event.events|=WriteEvent;CHKE update();}
    void disable_write(){event.events&=~WriteEvent;CHKE update();}
    void disable_all(){event.events=NoneEvent;CHKE update();state=2;}

    #undef CHKE

    void handle(){
        if((revents&EPOLLHUP)&&!(revents&EPOLLIN)){
            if(close_cb) close_cb();
        }

        if(revents&EPOLLERR){
            DBX(revents)
            if(error_cb) error_cb();
        }

        if(revents&(EPOLLIN|EPOLLPRI|EPOLLRDHUP|EPOLLRDNORM)){
            if(read_cb) read_cb();
        }

        if(revents&(EPOLLOUT|EPOLLWRNORM)){
            if(write_cb) write_cb();
        }
    }

    private:

    static const ui NoneEvent=0u;
    static const ui ReadEvent=EPOLLIN|EPOLLPRI;
    static const ui WriteEvent=EPOLLOUT;
};