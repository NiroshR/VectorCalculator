#include "GreeterClient.hpp"

GreeterClient::GreeterClient(std::shared_ptr<Channel> channel)
    : m_stub(Greeter::NewStub(channel)) {}

// Assembles the client's payload, sends it and presents the response back
// from the server.
std::string GreeterClient::SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = m_stub->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

int main() {
    std::string target_str = "localhost:50051";
    GreeterClient greeter(
        grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;
}