/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rpc_server.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/24 00:10:22
 * @brief 
 *  
 **/

#include "rpc_server.h"

#include <string>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>

#include "rpc_util.h"

namespace tp_rpc {

//using std::string;

#define MAXEVENTS 100

RpcServer::RpcServer() {
    Initialize();
}

RpcServer::~RpcServer() {
    for (HashMap::iterator iter = method_hashmap_.begin(); 
         iter != method_hashmap_.end();
         ++iter) {
        RpcMethod* rpc_method_ptr = iter->second;
        if (NULL != rpc_method_ptr) {
            delete rpc_method_ptr;
            rpc_method_ptr = NULL;
        }
    }
    delete worker_threads_ptr_;
    delete io_thread_ptr_;
    delete connection_manager_ptr_;
}

bool RpcServer::Initialize() {
    // should read from config file
    // strcpy(host_, "127.0.0.1");
    // strcpy(port_, "9998");
    connection_manager_ptr_ = new ConnectionManager();
    io_thread_ptr_ = new IOThread();
    worker_threads_ptr_ = new ThreadPool(20);

    return true;
}

RpcServer& RpcServer::GetInstance() {
    static RpcServer server_instance;
    return server_instance;
}

bool RpcServer::RegisteService(Service* reg_service) {
    const ServiceDescriptor* descriptor = reg_service->GetDescriptor();
    for (int32_t i = 0; i < descriptor->method_count(); ++i) {
        const MethodDescriptor* method_desc = descriptor->method(i);
        const Message* request = &reg_service->GetRequestPrototype(method_desc);
        const Message* response = &reg_service->GetResponsePrototype(method_desc);

        RpcMethod* rpc_method =
            new RpcMethod(reg_service, request, response, method_desc);

        uint32_t hash_code = BKDRHash(method_desc->full_name().c_str());

        HashMap::iterator ret_iter = method_hashmap_.find(hash_code);
        if (ret_iter == method_hashmap_.end()) {
            method_hashmap_.insert(std::make_pair(hash_code, rpc_method));
        } else {
            delete ret_iter->second;
            method_hashmap_[hash_code] = rpc_method;
        }
    }
   return true; 
}

bool RpcServer::Start() {

    io_thread_ptr_->Start();
    worker_threads_ptr_->Start();

    io_thread_ptr_->Wait();
    worker_threads_ptr_->Wait();

}

bool RpcServer::RpcCall(int32_t event_fd) {
    if (NULL == worker_threads_ptr_) {
        return false;
    }
    CallBackParams* cb_params_ptr = new CallBackParams();
    cb_params_ptr->event_fd = event_fd;
    cb_params_ptr->rpc_server_ptr = this;
    worker_threads_ptr_->Processor(RpcServer::RpcProcessor, cb_params_ptr);
    return true;
}

ConnectionManager* RpcServer::GetConnectionManager() {
    return connection_manager_ptr_;
}

void* RpcServer::RpcProcessor(void *arg) {

    CallBackParams* cb_params_ptr = (CallBackParams*) arg;
    if (NULL == cb_params_ptr) {
        return NULL;
    }
    RpcServer* rpc_serv_ptr = cb_params_ptr->rpc_server_ptr;
    if (NULL == rpc_serv_ptr) {
        return NULL;
    }
    int32_t event_fd = cb_params_ptr->event_fd;

    Message* request;
    RpcMessage recv_rpc_msg;
    if (!rpc_serv_ptr->GetMethodRequest(event_fd, recv_rpc_msg, request)) {
        fprintf(stderr, "get method request failed!\n");
        rpc_serv_ptr->ErrorSendMsg(event_fd, "get method request failed!");
        return NULL;
    }

    uint32_t hash_code = recv_rpc_msg.head_code();
    HashMap& method_hashmap = rpc_serv_ptr->method_hashmap_;
    HashMap::iterator method_iter = method_hashmap.find(hash_code);
    if (method_iter == method_hashmap.end() || NULL == method_iter->second) {
        fprintf(stderr, "find hash code failed! %u\n", hash_code);
        rpc_serv_ptr->ErrorSendMsg(event_fd, "find hash code failed!");
        return NULL;
    }
    RpcMethod* rpc_method = method_iter->second;
    request = rpc_method->request->New();
    if (!request->ParseFromString(recv_rpc_msg.body_msg())) {
        fprintf(stderr, "parse body msg error!");
        rpc_serv_ptr->ErrorSendMsg(event_fd, "parse body msg error!");
        delete request;
        return NULL;
    }

    const MethodDescriptor* method_desc = rpc_method->method;
    Message* response = rpc_method->response->New();
    rpc_method->service->CallMethod(method_desc, NULL, request, response, NULL);
    
    if (!rpc_serv_ptr->SendFormatStringMsg(event_fd, response)) {
        fprintf(stderr, "send format response failed!\n");
        rpc_serv_ptr->ErrorSendMsg(event_fd, "send format response failed!");
    }
    delete request;
    delete response;
    delete cb_params_ptr;
}


bool RpcServer::GetMethodRequest(int32_t event_fd, RpcMessage& recv_rpc_msg, Message* request) {
    string msg_str;
    if (connection_manager_ptr_->EpollRecvMsg(event_fd, msg_str) < 0) {
        fprintf(stderr, "connection_manager recv msg failed!");
        return false;
    }

    if (!recv_rpc_msg.ParseFromString(msg_str)) {
        fprintf(stderr, "parse from string msg failed!");
        return false;
    }
    return true;
}

bool RpcServer::SendFormatStringMsg(int32_t event_fd, Message* response) {
    string response_str;
    if (!response->SerializeToString(&response_str)) {
        fprintf(stderr, "response_str SerializeToString failed!\n");
        return false;
    }

    RpcMessage send_rpc_msg;
    send_rpc_msg.set_head_code(200);
    send_rpc_msg.set_body_msg(response_str);
    string send_str;
    if (!send_rpc_msg.SerializeToString(&send_str)) {
        fprintf(stderr, "send_str SerializeToString failed!\n");
        return false;
    }
    connection_manager_ptr_->EpollSendMsg(event_fd, send_str);

    return true;
}

bool RpcServer::ErrorSendMsg(int32_t event_fd, const string& error_msg) {
    RpcMessage error_rpc_msg;
    // 500 means internal error
    error_rpc_msg.set_head_code(500);
    error_rpc_msg.set_body_msg(error_msg);

    string err_msg_str;
    if (!error_rpc_msg.SerializeToString(&err_msg_str)) {
        fprintf(stderr, "error send error!");
        return false;
    }
    connection_manager_ptr_->EpollSendMsg(event_fd, err_msg_str);
    return true;
}

}  // end of namespace tp_rpc





/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
