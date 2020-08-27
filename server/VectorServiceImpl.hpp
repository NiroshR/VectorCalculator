#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "vector.grpc.pb.h"

using calculus::Vector;
using calculus::VectorCalculator;
using calculus::VectorRequest;
using grpc::ServerContext;
using grpc::Status;

class VectorServiceImpl final : public VectorCalculator::Service {
   public:
    VectorServiceImpl();
    Status CrossProduct(::ServerContext* context,
                        const ::calculus::VectorRequest* request,
                        ::calculus::Vector* response) override;
};
