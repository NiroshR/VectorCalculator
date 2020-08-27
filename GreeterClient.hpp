#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "greeter.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using hello::world::Greeter;
using hello::world::HelloReply;
using hello::world::HelloRequest;

class GreeterClient {
   public:
    GreeterClient(std::shared_ptr<Channel> channel);
    ~GreeterClient() = default;

    std::string SayHello(const std::string& user);

   private:
    std::unique_ptr<Greeter::Stub> m_stub;
};