#include "helloworld.pb.h"
#include "helloworld.grpc.pb.h"
#include <grpc++/grpc++.h>
#include <string>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using helloworld::TestServer; // MathTest
using helloworld::HelloMessage; // MathRequest
using helloworld::Reply; // MathReply

class HelloServiceImplementation final : public TestServer::Service {
  Status hello_request(ServerContext* context, const HelloMessage* request, Reply* reply) final {
    auto a = request->a();
    auto b = request->b();
    throw 1;
    reply->set_result(a * b);
    return Status::OK;
  }
};

void Run() {
  std::string address("0.0.0.0:50001");
  HelloServiceImplementation service;
  ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on port: " << address << '\n';
  server->Wait();
}

int main(int argc, char** argv) {
  Run();
  return 0;
}
