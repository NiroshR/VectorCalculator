#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "vector.grpc.pb.h"

using calculus::Scalar;
using calculus::Vector;
using calculus::VectorCalculator;
using calculus::VectorMagnitudeRequest;
using calculus::VectorRequest;
using grpc::ServerContext;
using grpc::Status;

class VectorServiceImpl final : public VectorCalculator::Service {
   public:
    VectorServiceImpl();

    Status VectorCrossProduct(ServerContext* context,
                              const VectorRequest* request,
                              Vector* response) override;

    Status VectorCrossProductAbsolute(ServerContext* context,
                                      const VectorRequest* request,
                                      Scalar* response) override;

    Status MagnitudeCrossProduct(ServerContext* context,
                                 const VectorMagnitudeRequest* request,
                                 Scalar* response) override;

    Status DotProduct(ServerContext* context, const VectorRequest* request,
                      Scalar* response) override;

    Status MagnitudeDotProduct(ServerContext* context,
                               const VectorMagnitudeRequest* request,
                               Scalar* response) override;

    Status ScalarProjection(ServerContext* context,
                            const VectorRequest* request,
                            Scalar* response) override;

    Status VectorProjection(ServerContext* context,
                            const VectorRequest* request,
                            Vector* response) override;

    Status ApplicationVolumeParallelepiped(ServerContext* context,
                                           const VectorRequest* request,
                                           Scalar* response) override;

   private:
    void assignVectorValues(Vector* vec, double x, double y, double z);
    void crossProduct(const VectorRequest* request, Vector* response);
    double dotProduct(const VectorRequest* request);
    double vectorMagnitude(const Vector* vec);
};
