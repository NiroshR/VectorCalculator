#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "greeter.grpc.pb.h"

using hello::world::Greeter;
using hello::world::HelloReply;
using hello::world::HelloRequest;

class GreeterServiceImpl final : public Greeter::Service {
   public:
    GreeterServiceImpl();
    grpc::Status SayHello(grpc::ServerContext* context,
                          const HelloRequest* request,
                          HelloReply* reply) override;
};
