#include"event.h"
#include"loop.h"
#include"tcp_connection.h"

ll_event::ll_event(ll_loop *loop,int fd):loop(loop),revents(0),fd(fd),state(0){
    event.events=0;
    event.data.ptr=this;
    read_cb=nullptr;
    write_cb=nullptr;
    close_cb=nullptr;
    error_cb=nullptr;
}

void ll_event::update(){loop->update_event(this);}