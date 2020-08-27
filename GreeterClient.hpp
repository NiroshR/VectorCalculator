#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "greeter.grpc.pb.h"

using calculus::Vector;
using calculus::VectorCalculator;
using calculus::VectorRequest;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class GreeterClient {
   public:
    GreeterClient(std::shared_ptr<Channel> channel);
    ~GreeterClient() = default;

    std::string CrossProduct(const std::string& user);

   private:
    std::unique_ptr<VectorCalculator::Stub> m_stub;
};