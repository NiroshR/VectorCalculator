# Generating client and server code

## C++
```bash
protoc --grpc_out=cpp --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` vector.proto
protoc --cpp_out=cpp vector.proto
```