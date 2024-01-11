cmake_minimum_required(VERSION 3.22)


project(grpc-test
        VERSION 1.0.0
        DESCRIPTION "How grpc works"
        LANGUAGES CXX)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_executable(client)
cmake_path(SET PROTO_DIR "${CMAKE_CURRENT_BINARY_DIR}/proto")
protobuf_generate(
        TARGET client
        LANGUAGE cpp
        PROTOS helloworld.proto
        PROTOC_OUT_DIR "${PROTO_DIR}"
        GENERATE_EXTENSIONS .pb.h .pb.cc)

protobuf_generate(
        TARGET client
        LANGUAGE grpc
        PROTOS helloworld.proto
        PROTOC_OUT_DIR "${PROTO_DIR}"
        PLUGIN protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc)

target_sources(client
        PRIVATE
#        main.cpp
        server.cpp
        )

target_include_directories(client
        PRIVATE
        ${gRPC_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${PROTO_DIR}>
        )

target_link_libraries(client
        PRIVATE
        gRPC::grpc++
        protobuf::libprotobuf
        )