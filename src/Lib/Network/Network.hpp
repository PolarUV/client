#ifndef CLIENT_NETWORK_HPP
#define CLIENT_NETWORK_HPP

#include "Lib/Network/API/Packet.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/container/deque.hpp>

#include <chrono>
#include <limits>
#include <mutex>
#include <string>
#include <thread>

class Network {
public:
    Network() : socket_(ioContext_), thread_() {/*thread_ = std::thread(&Network::Run, this)*/;};

    Response TransferData(const Request &request);

    void TryConnect(const std::array<char, 16> &ip);

    bool IsActive() { return isActive_; }

private:
    static constexpr size_t BAD_ENDPOINT = std::numeric_limits<uint64_t>::max();
    static constexpr size_t PORT = 2022;
    static constexpr auto TRANSFER_TIMEOUT = std::chrono::milliseconds(2000);
    static constexpr auto CONNECTION_TIMEOUT = std::chrono::milliseconds(100);

    //void Run();

    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::socket socket_;
    boost::container::deque<Request> requests_;
    std::thread thread_;
    std::atomic<bool> isActive_;

    bool RunFor(std::chrono::steady_clock::duration timeout);
};

#endif  // CLIENT_NETWORK_HPP
