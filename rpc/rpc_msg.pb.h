// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rpc_msg.proto

#ifndef PROTOBUF_rpc_5fmsg_2eproto__INCLUDED
#define PROTOBUF_rpc_5fmsg_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_rpc_5fmsg_2eproto();
void protobuf_AssignDesc_rpc_5fmsg_2eproto();
void protobuf_ShutdownFile_rpc_5fmsg_2eproto();

class RpcMessage;

// ===================================================================

class RpcMessage : public ::google::protobuf::Message {
 public:
  RpcMessage();
  virtual ~RpcMessage();

  RpcMessage(const RpcMessage& from);

  inline RpcMessage& operator=(const RpcMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RpcMessage& default_instance();

  void Swap(RpcMessage* other);

  // implements Message ----------------------------------------------

  RpcMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RpcMessage& from);
  void MergeFrom(const RpcMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 head_code = 1 [default = 0];
  inline bool has_head_code() const;
  inline void clear_head_code();
  static const int kHeadCodeFieldNumber = 1;
  inline ::google::protobuf::uint32 head_code() const;
  inline void set_head_code(::google::protobuf::uint32 value);

  // optional string body_msg = 2 [default = ""];
  inline bool has_body_msg() const;
  inline void clear_body_msg();
  static const int kBodyMsgFieldNumber = 2;
  inline const ::std::string& body_msg() const;
  inline void set_body_msg(const ::std::string& value);
  inline void set_body_msg(const char* value);
  inline void set_body_msg(const char* value, size_t size);
  inline ::std::string* mutable_body_msg();
  inline ::std::string* release_body_msg();
  inline void set_allocated_body_msg(::std::string* body_msg);

  // @@protoc_insertion_point(class_scope:RpcMessage)
 private:
  inline void set_has_head_code();
  inline void clear_has_head_code();
  inline void set_has_body_msg();
  inline void clear_has_body_msg();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* body_msg_;
  ::google::protobuf::uint32 head_code_;
  friend void  protobuf_AddDesc_rpc_5fmsg_2eproto();
  friend void protobuf_AssignDesc_rpc_5fmsg_2eproto();
  friend void protobuf_ShutdownFile_rpc_5fmsg_2eproto();

  void InitAsDefaultInstance();
  static RpcMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// RpcMessage

// optional uint32 head_code = 1 [default = 0];
inline bool RpcMessage::has_head_code() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RpcMessage::set_has_head_code() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RpcMessage::clear_has_head_code() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RpcMessage::clear_head_code() {
  head_code_ = 0u;
  clear_has_head_code();
}
inline ::google::protobuf::uint32 RpcMessage::head_code() const {
  // @@protoc_insertion_point(field_get:RpcMessage.head_code)
  return head_code_;
}
inline void RpcMessage::set_head_code(::google::protobuf::uint32 value) {
  set_has_head_code();
  head_code_ = value;
  // @@protoc_insertion_point(field_set:RpcMessage.head_code)
}

// optional string body_msg = 2 [default = ""];
inline bool RpcMessage::has_body_msg() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RpcMessage::set_has_body_msg() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RpcMessage::clear_has_body_msg() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RpcMessage::clear_body_msg() {
  if (body_msg_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    body_msg_->clear();
  }
  clear_has_body_msg();
}
inline const ::std::string& RpcMessage::body_msg() const {
  // @@protoc_insertion_point(field_get:RpcMessage.body_msg)
  return *body_msg_;
}
inline void RpcMessage::set_body_msg(const ::std::string& value) {
  set_has_body_msg();
  if (body_msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    body_msg_ = new ::std::string;
  }
  body_msg_->assign(value);
  // @@protoc_insertion_point(field_set:RpcMessage.body_msg)
}
inline void RpcMessage::set_body_msg(const char* value) {
  set_has_body_msg();
  if (body_msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    body_msg_ = new ::std::string;
  }
  body_msg_->assign(value);
  // @@protoc_insertion_point(field_set_char:RpcMessage.body_msg)
}
inline void RpcMessage::set_body_msg(const char* value, size_t size) {
  set_has_body_msg();
  if (body_msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    body_msg_ = new ::std::string;
  }
  body_msg_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:RpcMessage.body_msg)
}
inline ::std::string* RpcMessage::mutable_body_msg() {
  set_has_body_msg();
  if (body_msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    body_msg_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:RpcMessage.body_msg)
  return body_msg_;
}
inline ::std::string* RpcMessage::release_body_msg() {
  clear_has_body_msg();
  if (body_msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = body_msg_;
    body_msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void RpcMessage::set_allocated_body_msg(::std::string* body_msg) {
  if (body_msg_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete body_msg_;
  }
  if (body_msg) {
    set_has_body_msg();
    body_msg_ = body_msg;
  } else {
    clear_has_body_msg();
    body_msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:RpcMessage.body_msg)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rpc_5fmsg_2eproto__INCLUDED
