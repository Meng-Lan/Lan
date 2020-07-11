#include<bits/stdc++.h>
#include"tcp_server.h"
#include"control.h"

#define forever for(;;)

const char response[]="HTTP/1.1 200 OK\r\nConnection: close\r\ncontent-length: 0\r\n\r\n";

void read_cb(ll_tcp_connection *conn,std::shared_ptr<char> input,int len){
    // std::string in(input.get(),input.get()+len);
    // cout<<"request:\n"<<in<<endl;
    static const int size=strlen(response);
    char *p=new char[1024];
    // PV(p);
    memcpy(p,response,size);
    // cout<<"response:\n"<<response;
    conn->send(std::shared_ptr<char>(p),size);
}


int main(){
    // PV(EPOLLIN)PV(EPOLLOUT)PV(EPOLLRDHUP)PV(EPOLLPRI)PV(EPOLLERR)PV(EPOLLHUP)PV(EPOLLET)PV(EPOLLONESHOT)PV(EPOLLWAKEUP)PV(EPOLLWRNORM)PV(EPOLLRDNORM)

    // DBX(std::this_thread::get_id());
    ll_tcp_server server(1);
    server.start();
    connection_callback conn_cb;
    conn_cb.read_cb=read_cb;
    server.listen(51920,conn_cb);

    bool first=true;
    printf("ok\n");
    forever{
        // if(first) {cout<<"ok"<<endl;first=false;}
        sleep(2);
        PV(control::now_epoll_act_cnt);
        cout<<"now act: ";
        for(auto &v:control::now_epoll_act){
            ll_event *e=(ll_event*)v.data.ptr;
            cout<<"("<<e->fd<<","<<e->revents<<","<<e->event.events<<") ";
        }
        cout<<endl;
        PV(control::now_listen_sz);
        PV(control::now_connection_sz);
        PV(control::handle_conn_sz);
        PV(control::handle_close_sz);
        cout<<endl;
    }

    return 0;
}