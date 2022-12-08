#include "Network.hpp"
#include "Logger/Logger.hpp"

#include <cstdint>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using ErrorCode = boost::system::error_code;
using ConstBuffer = boost::asio::const_buffer;
using MutableBuffer = boost::asio::mutable_buffer;

constexpr size_t REQUEST_HEADER_SIZE = sizeof(Request::HeaderType);
constexpr size_t RESPONSE_HEADER_SIZE = sizeof(Response::HeaderType);

void Network::TryConnect(const std::array<char, 16> &ip) {
    using endpoint_t = boost::asio::ip::tcp::resolver::endpoint_type;

    if (isActive_) [[unlikely]] {
        return;
    }

    ErrorCode errorCode{};
    const auto address = boost::asio::ip::make_address(ip.data(), errorCode);

    if (errorCode) [[unlikely]]{
        PolarError << "Error during creating ip: " << errorCode.message();
        return;
    }

    const endpoint_t endpoint(address, PORT);

    bool error = false;

    socket_.async_connect(endpoint, [&](const ErrorCode &errorCode) {
        if (errorCode.failed()) {
            error = true;
        }
    });

    const bool result = RunFor(CONNECTION_TIMEOUT) && !error;

    PolarProfile << "Try connected, the state is: " << result;

    isActive_.exchange(result);
}

bool Network::RunFor(std::chrono::steady_clock::duration timeout) {
    ioContext_.restart();

    ioContext_.run_for(timeout);

    if (ioContext_.stopped()) {
        return true;
    }

    socket_.close();
    ioContext_.run();
    return false;
}

Response Network::TransferData(const Request &request) {
    using namespace boost::asio;
    using namespace std::chrono_literals;

    std::string responseData;
    Response::HeaderType responseHeader;
    const std::array<ConstBuffer, 2> requestData{ConstBuffer(&request.Header, REQUEST_HEADER_SIZE),
                                                 ConstBuffer(request.Data.data(), request.Header.Length)};

    auto setErrorData = [](std::string &data, Response::HeaderType &header, SSIZE_T endpointId) {
        data = "";
        header.Code = Response::ConnectionError;
        header.EndpointId = endpointId;
    };

    auto readDataCallback = [&](const ErrorCode &errorCode, size_t bytes) {
        if (errorCode.failed() || bytes != responseHeader.Length) {
            setErrorData(responseData, responseHeader, request.Header.EndpointId);
        }
    };

    auto readHeaderCallback = [&](const ErrorCode &errorCode, size_t bytes) {
        if (errorCode.failed() || bytes != sizeof(Response::HeaderType)) {
            setErrorData(responseData, responseHeader, request.Header.EndpointId);
            return;
        }

        responseData = std::string(responseHeader.Length, 0);

        async_read(socket_, MutableBuffer(responseData.data(), responseHeader.Length),
                   transfer_exactly(responseHeader.Length), readDataCallback);
    };

    auto requestCallback = [&](const ErrorCode &errorCode, size_t bytes) {
        if (errorCode.failed() || bytes != sizeof(Request::HeaderType) + request.Header.Length) {
            setErrorData(responseData, responseHeader, request.Header.EndpointId);
            return;
        }

        async_read(socket_, MutableBuffer(&responseHeader, RESPONSE_HEADER_SIZE),
                   transfer_exactly(RESPONSE_HEADER_SIZE), readHeaderCallback);
    };

    async_write(socket_, requestData, transfer_exactly(REQUEST_HEADER_SIZE + request.Header.Length), requestCallback);

    if (!RunFor(TRANSFER_TIMEOUT)) {
        setErrorData(responseData, responseHeader, request.Header.EndpointId);
    }

    return {std::move(responseData), responseHeader.Code, responseHeader.EndpointId};
}
