#include"listener.h"
#include"loop.h"
#include"tcp_connection.h"
#include"control.h"
#include<error.h>

ll_listener::ll_listener(ll_loop *loop,int port):loop(loop),fd(::socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC,IPPROTO_TCP))
,event(loop,fd){
    ASS(fd)
    int optval=1;
    int ret=setsockopt(fd,SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    ASS(ret!=-1)
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr.sin_port = htons(port);
    ret=bind(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    ASS(ret!=-1)
    event.read_cb=std::bind(&ll_listener::handle_read,this);
}

void ll_listener::listen(){
    int ret=::listen(fd,SOMAXCONN);
    // DBX(fd)
    ASS(ret!=-1)
    event.enable_read();
    control::now_listen_sz++;
}

void ll_listener::handle_read(){
    int connfd;
    do{
        struct sockaddr peeraddr;
        socklen_t len=sizeof(struct sockaddr);
        connfd=::accept4(fd,&peeraddr,&len,SOCK_NONBLOCK|SOCK_CLOEXEC);
        // DBX(connfd);
        if(connfd>=0){
            // DBX(loop->thread_id)
            if(!conn_cb.empty()) new_connection(connfd,peeraddr);
            else {assert(::close(connfd)>=0);DBX("close connfd")}
        }
    }while(connfd>=0);
    int ret=errno;
    ASS(ret==EAGAIN||ret==EWOULDBLOCK);
}

void ll_listener::new_connection(int fd,const struct sockaddr &addr){
    tcp_connection_ptr conn(new ll_tcp_connection(loop,fd,addr));
    conn->connection_cb=conn_cb.connection_cb;
    conn->read_cb=conn_cb.read_cb;
    conn->write_cb=conn_cb.write_cb;
    conn->close_cb=conn_cb.close_cb;
    using namespace std::placeholders;
    conn->destory_cb=std::bind(&ll_listener::destory_connection,this,_1);
    // PV(fd);
    ASS(connections.count(fd)==0);
    connections[fd]=conn;
    //fix
    loop->run_in_loop(std::bind(&ll_tcp_connection::connect_established,conn));
}

void ll_listener::destory_connection(int fd){
    loop->run_in_loop(std::bind(&ll_listener::erase_connection,this,fd));
}

void ll_listener::erase_connection(int fd){
    // printf("erase fd:%d\n",fd);
    ASS(connections[fd].use_count()==1);
    connections.erase(fd);
}