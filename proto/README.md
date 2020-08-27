protoc --grpc_out=cpp --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` greeter.proto
protoc --cpp_out=cpp greeter.proto