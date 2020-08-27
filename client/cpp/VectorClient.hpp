#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "vector.grpc.pb.h"

using calculus::Scalar;
using calculus::Vector;
using calculus::VectorCalculator;
using calculus::VectorMagnitudeRequest;
using calculus::VectorRequest;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class VectorClient {
   public:
    VectorClient(std::shared_ptr<Channel> channel);
    ~VectorClient() = default;

    std::string VectorCrossProduct(const std::string& user);
    std::string VectorCrossProductAbsolute(const std::string& user);
    std::string MagnitudeCrossProduct(const std::string& user);
    std::string DotProduct(const std::string& user);
    std::string MagnitudeDotProduct(const std::string& user);
    std::string ScalarProjection(const std::string& user);
    std::string VectorProjection(const std::string& user);
    std::string ApplicationVolumeParallelepiped(const std::string& user);

   private:
    std::unique_ptr<VectorCalculator::Stub> m_stub;
};