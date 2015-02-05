
#SUBDIRS=src
#DIST_SUBDIRS=src

bin_PROGRAMS = rpc_client rpc_server

rpc_client_SOURCES = \
		      ../cs_sample/client.cc \
		      ../cs_sample/proto/simple_rpc.pb.h \
		      ../cs_sample/proto/simple_rpc.pb.cc \
			  ../rpc/connection_manager.h \
			  ../rpc/connection_manager.cpp \
			  ../rpc/rpc_channel.h \
			  ../rpc/rpc_channel.cpp \
			  ../rpc/rpc_msg.pb.h \
			  ../rpc/rpc_msg.pb.cc \
			  ../rpc/rpc_util.h \
			  ../rpc/rpc_util.cpp

#INCLUDES = -I../third-64/libevent/include/
#CXXFLAGS = -std=c++11 -Wall -g -fPIC
rpc_client_CPPFLAGS = -I../../third-64/protobuf/include/
rpc_client_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
rpc_client_LDADD = -lpthread -lz -ldl -lrt  \
	               ../../third-64/protobuf/lib/*.a 
#http_server_a_LDADD = ../third-64/libevent/lib/*.a

rpc_server_SOURCES = \
		      ../cs_sample/server.cc \
		      ../cs_sample/proto/simple_rpc.pb.h \
		      ../cs_sample/proto/simple_rpc.pb.cc \
			  ../rpc/connection_manager.h \
			  ../rpc/connection_manager.cpp \
			  ../rpc/rpc_server.h \
			  ../rpc/rpc_server.cpp \
			  ../rpc/io_thread.h \
			  ../rpc/io_thread.cpp \
			  ../rpc/thread_pool.h \
			  ../rpc/thread_pool.cpp \
			  ../rpc/rpc_util.h \
			  ../rpc/rpc_util.cpp \
			  ../rpc/rpc_msg.pb.h \
			  ../rpc/rpc_msg.pb.cc

#INCLUDES = -I../third-64/libevent/include/
#CXXFLAGS = -std=c++11 -Wall -g -fPIC
rpc_server_CPPFLAGS = -I../../third-64/protobuf/include/ \
					   -I../../third-64/boost/include/ \
					   -I../../util/thread/include/ \
					   -I../../util/tools/include/
rpc_server_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
rpc_server_LDADD = -lpthread -lz -ldl -lrt  \
					../../third-64/protobuf/lib/*.a \
					../../third-64/boost/lib/*.a
#
