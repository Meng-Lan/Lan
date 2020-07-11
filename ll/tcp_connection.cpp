#include"tcp_connection.h"
#include"loop.h"
#include"control.h"


ll_tcp_connection::ll_tcp_connection(ll_loop *loop,int fd,const struct sockaddr &addr):loop(loop),fd(fd),addr(addr),event(loop,fd),state(connecting){
        event.read_cb=std::bind(&ll_tcp_connection::handle_read,this);
        event.close_cb=std::bind(&ll_tcp_connection::handle_close,this);
        event.error_cb=std::bind(&ll_tcp_connection::handle_error,this);
        //TODO
        connection_cb=nullptr;
        read_cb=nullptr;
        write_cb=nullptr;
        close_cb=nullptr;
        destory_cb=nullptr;
    }

ll_tcp_connection::~ll_tcp_connection(){
    control::handle_close_sz++;
    if(state!=disconnection){
        printf("in unexpected\n");
        state=disconnection;
        event.disable_all();
        ::shutdown(fd,SHUT_RDWR);
    }
    int ret=::close(fd);
    ASS(ret!=-1);
}

void ll_tcp_connection::connect_established(){
    event.enable_read();
    if(connection_cb) connection_cb(this);
    state=connected;
    control::handle_conn_sz++;
}

void ll_tcp_connection::handle_read(){
    if(state!=connected) DBX(fd);
    size_t len=1<<16;
    char *input=new char[len];
    ssize_t n=::read(fd,input,len);
    std::shared_ptr<char> ptr(input);

    if(n>0){read_cb(this,ptr,n);}
    else if(n==0) handle_close();
    else handle_error();
}

void ll_tcp_connection::handle_close(){
    assert(state!=disconnection);
    state=disconnection;
    event.disable_all();
    ::shutdown(fd,SHUT_RDWR);
    destory_cb(fd);
}

void ll_tcp_connection::handle_error(){
    // int ret=errno;
    PV(errno);
    // if(ret!=EAGAIN&&ret!=EWOULDBLOCK) handle_close();
}

void ll_tcp_connection::send(std::shared_ptr<char> ptr,int len){
    // PV(loop->is_in_loop_thread());
    if(loop->is_in_loop_thread()){
        send_in_loop(ptr,len);
    }
    else{
        void (ll_tcp_connection::*fp)(std::shared_ptr<char>,int)=&ll_tcp_connection::send_in_loop;
        loop->run_in_loop(std::bind(fp,this,ptr,len));
    }
}

void ll_tcp_connection::send_in_loop(std::shared_ptr<char> ptr,int len){
    auto n=::send(fd,ptr.get(),len,0);
    ASS(n==len);
}
