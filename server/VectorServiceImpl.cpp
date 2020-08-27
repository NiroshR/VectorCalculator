#include "VectorServiceImpl.hpp"

#include <grpc/grpc.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <cmath>
#include <memory>
#include <string>

#define PI 3.14159265359

using grpc::Server;
using grpc::ServerBuilder;

VectorServiceImpl::VectorServiceImpl() {}

Status VectorServiceImpl::VectorCrossProduct(ServerContext* context,
                                             const VectorRequest* request,
                                             Vector* response) {
    crossProduct(request, response);

    return Status::OK;
}

Status VectorServiceImpl::VectorCrossProductAbsolute(
    ServerContext* context, const VectorRequest* request, Scalar* response) {
    Vector* vec = new Vector();
    crossProduct(request, vec);

    response->set_value(vectorMagnitude(vec));

    delete vec;
    vec = nullptr;

    return Status::OK;
}

Status VectorServiceImpl::MagnitudeCrossProduct(
    ServerContext* context, const VectorMagnitudeRequest* request,
    Scalar* response) {
    double tmp = sin(request->angle() * PI / 180);
    response->set_value(request->mag1() * request->mag2() * tmp);

    return Status::OK;
}

Status VectorServiceImpl::DotProduct(ServerContext* context,
                                     const VectorRequest* request,
                                     Scalar* response) {
    response->set_value(dotProduct(request));
    return Status::OK;
}

Status VectorServiceImpl::MagnitudeDotProduct(
    ServerContext* context, const VectorMagnitudeRequest* request,
    Scalar* response) {
    double tmp = cos(request->angle() * PI / 180);
    response->set_value(request->mag1() * request->mag2() * tmp);

    return Status::OK;
}

Status VectorServiceImpl::ScalarProjection(ServerContext* context,
                                           const VectorRequest* request,
                                           Scalar* response) {
    double dot = dotProduct(request);
    auto tmp = request->second();
    double mag = vectorMagnitude(&tmp);
    response->set_value(dot / mag);
    return Status::OK;
}

Status VectorServiceImpl::VectorProjection(ServerContext* context,
                                           const VectorRequest* request,
                                           Vector* response) {
    double dot = dotProduct(request);
    auto tmp = request->second();
    double mag = vectorMagnitude(&tmp);
    double scalar = dot / mag;
    auto vec2 = request->second();
    assignVectorValues(response, scalar * vec2.x(), scalar * vec2.y(),
                       scalar * vec2.z());
    return Status::OK;
}

Status VectorServiceImpl::ApplicationVolumeParallelepiped(
    ServerContext* context, const VectorRequest* request, Scalar* response) {
    Vector* vec = new Vector();
    crossProduct(request, vec);

    auto vec3 = request->third();

    double x = vec->x() * vec3.x();
    double y = vec->y() * vec3.y();
    double z = vec->z() * vec3.z();

    delete vec;
    vec = nullptr;

    response->set_value(fabs(x + y + z));

    return Status::OK;
}

void VectorServiceImpl::assignVectorValues(Vector* vec, double x, double y,
                                           double z) {
    vec->set_x(x);
    vec->set_y(y);
    vec->set_z(z);
}

void VectorServiceImpl::crossProduct(const VectorRequest* request,
                                     Vector* response) {
    auto vec1 = request->first();
    auto vec2 = request->second();

    double x = (vec1.y() * vec2.z()) - (vec1.z() * vec2.y());
    double y = (vec1.z() * vec2.x()) - (vec1.x() * vec2.z());
    double z = (vec1.x() * vec2.y()) - (vec1.y() * vec2.x());

    assignVectorValues(response, x, y, z);
}

double VectorServiceImpl::dotProduct(const VectorRequest* request) {
    auto vec1 = request->first();
    auto vec2 = request->second();

    double x = vec1.x() * vec2.x();
    double y = vec1.y() * vec2.y();
    double z = vec1.z() * vec2.z();

    return x + y + z;
}

double VectorServiceImpl::vectorMagnitude(const Vector* vec) {
    return sqrt(vec->x() * vec->x() + vec->y() * vec->y() +
                vec->z() * vec->z());
}

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    VectorServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();

    return 0;
}