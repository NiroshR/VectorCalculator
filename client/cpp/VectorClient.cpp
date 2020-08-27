#include "VectorClient.hpp"

VectorClient::VectorClient(std::shared_ptr<Channel> channel)
    : m_stub(VectorCalculator::NewStub(channel)) {}

// Assembles the client's payload, sends it and presents the response back
// from the server.
std::string VectorClient::VectorCrossProduct(const std::string& user) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorRequest request;
    Vector reply;

    // The actual RPC.
    Status status = m_stub->VectorCrossProduct(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return std::to_string(reply.y());
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

int main() {
    std::string target_str = "localhost:50051";
    VectorClient client(
        grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = client.VectorCrossProduct(user);
    std::cout << "Computation received: " << reply << std::endl;
}