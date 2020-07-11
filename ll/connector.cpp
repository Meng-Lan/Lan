#include"connector.h"
#include"loop.h"
#include"tcp_connection.h"

ll_connector::ll_connector(ll_loop *loop,char *ipaddr,int port,connection_callback &conn):loop(loop),ip(ipaddr),port(port),fd(::socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC,IPPROTO_TCP)),try_cnt(0),conn_cb(conn){
    {
        ll_spin_guard guard(spin);
        connector_id=connector_num++;
    }
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr(ipaddr);
    sockaddr.sin_port = htons(port);
    int ret=::connect(fd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    ASS(ret);
    if(!ret){
        new_connection(fd,sockaddr);
    }
    else loop->run_in_loop(std::bind(&ll_connector::retry,this));
}

void ll_connector::new_connection(int fd,struct sockaddr_in &addr){
    struct sockaddr t_addr;
    memcpy(&t_addr,&addr,sizeof(addr));
    tcp_connection_ptr conn(new ll_tcp_connection(loop,fd,t_addr));
    conn->connection_cb=conn_cb.connection_cb;
    conn->read_cb=conn_cb.read_cb;
    conn->write_cb=conn_cb.write_cb;
    conn->close_cb=conn_cb.close_cb;
    using namespace std::placeholders;
    conn->destory_cb=std::bind(&ll_connector::destory_connection,this,_1);
    connection=conn;
    loop->run_in_loop(std::bind(&ll_tcp_connection::connect_established,conn));
}

void ll_connector::destory_connection(int fd){
    loop->run_in_loop(std::bind(&ll_connector::erase_connection,this,fd));
}

void ll_connector::erase_connection(int fd){
    ASS(fd==this->fd);
    connection=NULL;
}

void ll_connector::retry(){
    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    int ret=::connect(fd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    if(!ret) new_connection(fd,sockaddr);
    else loop->run_in_loop(std::bind(&ll_connector::retry,this));
}

int ll_connector::connector_num=0;
ll_spin ll_connector::spin;