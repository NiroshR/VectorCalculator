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
        return "OK";
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

std::string VectorClient::VectorCrossProductAbsolute(const std::string& user) {
    // Context for the client. It could be used to
    // convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorRequest request;
    Scalar reply;

    // The actual RPC.
    Status status =
        m_stub->VectorCrossProductAbsolute(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return "OK";
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

std::string VectorClient::MagnitudeCrossProduct(const std::string& user) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorMagnitudeRequest request;
    Scalar reply;

    // The actual RPC.
    Status status = m_stub->MagnitudeCrossProduct(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return "OK";
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

std::string VectorClient::DotProduct(const std::string& user) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorRequest request;
    Scalar reply;

    // The actual RPC.
    Status status = m_stub->DotProduct(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return "OK";
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

std::string VectorClient::MagnitudeDotProduct(const std::string& user) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorMagnitudeRequest request;
    Scalar reply;

    // The actual RPC.
    Status status = m_stub->MagnitudeDotProduct(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return "OK";
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

std::string VectorClient::ScalarProjection(const std::string& user) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorRequest request;
    Scalar reply;

    // The actual RPC.
    Status status = m_stub->ScalarProjection(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return "OK";
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

std::string VectorClient::VectorProjection(const std::string& user) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorRequest request;
    Vector reply;

    // The actual RPC.
    Status status = m_stub->VectorProjection(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return "OK";
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return "RPC failed";
    }
}

std::string VectorClient::ApplicationVolumeParallelepiped(
    const std::string& user) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    VectorRequest request;
    Scalar reply;

    // The actual RPC.
    Status status =
        m_stub->ApplicationVolumeParallelepiped(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
        return "OK";
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
    std::cout << "VectorCrossProduct received: " << reply << std::endl;
    reply = client.VectorCrossProductAbsolute(user);
    std::cout << "VectorCrossProductAbsolute received: " << reply << std::endl;
    reply = client.MagnitudeCrossProduct(user);
    std::cout << "MagnitudeCrossProduct received: " << reply << std::endl;
    reply = client.DotProduct(user);
    std::cout << "DotProduct received: " << reply << std::endl;
    reply = client.MagnitudeDotProduct(user);
    std::cout << "MagnitudeDotProduct received: " << reply << std::endl;
    reply = client.ScalarProjection(user);
    std::cout << "ScalarProjection received: " << reply << std::endl;
    reply = client.VectorProjection(user);
    std::cout << "VectorProjection received: " << reply << std::endl;
    reply = client.ApplicationVolumeParallelepiped(user);
    std::cout << "ApplicationVolumeParallelepiped received: " << reply
              << std::endl;
}
