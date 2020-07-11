#include"epoll.h"
#include"control.h"

void ll_epoll::poll(std::vector<ll_event*> &events){
    events.clear();
    auto cnt=::epoll_wait(epfd,&*temp_events.begin(),(int)temp_events.size(),timeout);
    ASS(cnt!=-1)
    control::now_epoll_act_cnt=cnt;
    control::now_epoll_act.assign(temp_events.begin(),temp_events.begin()+cnt);
    for(int i=0;i<cnt;++i){
        ll_event *tevent=(ll_event*)temp_events[i].data.ptr;
        tevent->revents=temp_events[i].events;
        events.push_back(tevent);
    }
    if((ui)cnt==temp_events.size()){
        temp_events.resize(temp_events.size()*2);
    }
}

void ll_epoll::update_event(ll_event *event){
    const int &state=event->state;
    if(state==sNew||state==sDelete){
        update(EPOLL_CTL_ADD,event);
        event->state=sAdd;
    }
    else{
        if(event->event.events==0) {update(EPOLL_CTL_DEL,event);}
        else update(EPOLL_CTL_MOD,event);
    }
}

