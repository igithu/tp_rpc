/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file io_thread.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/05 16:02:39
 * @brief 
 *  
 **/

#include "io_thread.h"

//#include <sys/epoll.h>
#include <sys/socket.h>

#include "rpc_server.h"

namespace simple_rpc_v2 {

#define MAXEVENTS 100

IOThread::IOThread() {
}

IOThread::~IOThread() {
}

void IOThread::Run() {
    RpcServer& rpc_server = RpcServer::GetInstance();
    ConnectionManager* connection_manager_ptr = rpc_server.GetConnectionManager();
    if (NULL == connection_manager_ptr) {
        return;
    }
    int32_t listenfd = connection_manager_ptr->TcpListen();
    if (connection_manager_ptr->EpollInit(listenfd) < 0) {
        fprintf(stderr, "epollInit failed!\n");
        return;
    }
    struct epoll_event events[MAXEVENTS];
    while (true) {
        int32_t ready = connection_manager_ptr->EpollWait(MAXEVENTS, events);
        for (int32_t i = 0; i < ready; ++i) {
            int32_t event_fd = events[i].data.fd;
            uint32_t cur_events = events[i].events;
            if (event_fd == listenfd) {
                printf("new connection\n");
                connection_manager_ptr->EpollNewConnect(listenfd);
            } else if (cur_events & EPOLLIN) {
                rpc_server.RpcCall(event_fd);
            }
        }
    }

}

}  // end of namespace simple_rpc_v2




/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
