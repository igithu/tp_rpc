/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rpc_channel.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/23 16:25:13
 * @brief 
 *  
 **/


#include "rpc_channel.h"

#include "rpc_util.h"
#include "rpc_msg.pb.h"

namespace simple_rpc_v2 {

Channel::Channel(const string& host, int32_t port) {
}

Channel::~Channel() {
}

// used by CallMethod
bool FormatSendMsg(
        const MethodDescriptor* method, const Message* request, string& send_str);
// used by CallMethod
bool FormatRecvMsg(
        const string& recv_str, Message* response);

void Channel::CallMethod(const MethodDescriptor* method,
                         RpcController* control,
                         const Message* request,
                         Message* response,
                         Closure* done) {

    // bad desgin
    // const FieldDescriptor* method_code_field =
    //     request->GetDescriptor()->FindFieldByName("method_code");
    // const Reflection* reflection = request->GetReflection();
    // reflection->SetUInt32(request, method_code_field, hash_code);

    // too complex
    // size_t msg_len = request->ByteSize() + code_size + 1;
    // char send_content[msg_len];
    // memcpy(send_content, hash_code, sizeof(hash_code));

    // if (!request->SerializeToArray((char*)send_content + sizeof(hash_code), msg_len)) {
    //     fprintf(stderr, "request SerializeToString has failed!");
    //     return;
    // }

    string send_str;
    if (!FormatSendMsg(method, request, send_str)) {
        return;
    }
  
    int32_t connect_fd = connection_manager_.TcpConnect();
    if (connect_fd < 0) {
        fprintf(stderr, "rpc connect server failed!\n");
        return;
    }
    connection_manager_.SendMsg(connect_fd, send_str);

    string recv_str;
    connection_manager_.RecvMsg(connect_fd, recv_str);
    close(connect_fd);

    if (!FormatRecvMsg(recv_str, response)) {
        fprintf(stderr, "format recv msg failed!\n");
    }
}

void Channel::Close() {
}

bool FormatSendMsg(
        const MethodDescriptor* method, const Message* request, string& send_str) {

    uint32_t hash_code = BKDRHash(method->full_name().c_str());

    if (NULL == request) {
        fprintf(stderr, "request is null ptr!\n");
        return false;
    }

    string request_str;
    if (!request->SerializeToString(&request_str)) {
        fprintf(stderr, "request SerializeToString has failed!");
        return false;
    }
    RpcMessage rpc_msg;
    rpc_msg.set_head_code(hash_code);
    rpc_msg.set_body_msg(request_str);

    if (!rpc_msg.SerializeToString(&send_str)) {
        fprintf(stderr, "request SerializeToString has failed!\n");
        return false;
    }
    return true;
}

bool FormatRecvMsg(const string& recv_str, Message* response) {
    RpcMessage recv_rpc_msg;
    if (!recv_rpc_msg.ParseFromString(recv_str)) {
        fprintf(stderr, "parse recv msg error! %s\n", recv_str.c_str());
        return false;
    }

    if (500 == recv_rpc_msg.head_code()) {
        fprintf(stderr, "server internal error\n");
    }

    if (!response->ParseFromString(recv_rpc_msg.body_msg())) {
        fprintf(stderr, "parse recv body msg error!\n");
        return false;
    }
    return true;
}


}  // end of namespace simple_rpc_v2



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
