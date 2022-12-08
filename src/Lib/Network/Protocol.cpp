#include "API/Protocol.hpp"

#include "Compressor.hpp"
#include "Network.hpp"

Network* Get() {
    static Network network;
    return &network;
}

Protocol::Protocol() : network_(Get()) {}

Response Protocol::SendReadRequest(uint64_t endpoint) {
    const auto request = Request("", Request::TypeEnum::R, endpoint);

    const auto tmp = network_->TransferData(request);

    auto decompressed = Decompress(tmp.Data);

    Response response(std::move(decompressed), tmp.Header.Code, tmp.Header.EndpointId);

    return response;
}

Response Protocol::SendWriteRequest(const std::string_view& data, uint64_t endpoint) {
    auto compressed = Compress(data);

    const auto request = Request({compressed.data(), compressed.size()}, Request::TypeEnum::W, endpoint);

    auto response = network_->TransferData(request);

    return response;
}

Response Protocol::SendWriteReadRequest(const std::string_view& data, uint64_t endpoint) {
    auto compressed = Compress(data);

    const auto request = Request({compressed.data(), compressed.size()}, Request::TypeEnum::WR, endpoint);

    auto tmp = network_->TransferData(request);

    auto decompressed = Decompress(tmp.Data);

    Response response(std::move(decompressed), tmp.Header.Code, tmp.Header.EndpointId);

    return response;
}

void Protocol::Connect(const std::array<char, 16> &ip) {
    network_->TryConnect(ip);
}

bool Protocol::IsActive() {
    return network_->IsActive();
}
