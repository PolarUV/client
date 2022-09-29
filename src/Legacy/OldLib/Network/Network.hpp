#ifndef CLIENT_TCPSESSION_HPP
#define CLIENT_TCPSESSION_HPP

#include <queue>
#include <shared_mutex>

#include <boost/asio.hpp>
#include <QObject>

#include <Exceptions/Exceptions.hpp>
#include "Singleton.hpp"
#include "ThreadSafeQueue/ThreadSafeQueue.hpp"
#include "Packet.hpp"

#include <iostream>

namespace lib::network {

    class Network {
    public:

        static constexpr std::chrono::milliseconds CONNECTION_TIMEOUT = std::chrono::milliseconds(100);

        static constexpr int COMPRESS_LVL = 22;

        static constexpr auto TRANSFER_TIMEOUT =
#ifdef DEBUG
        std::chrono::milliseconds(2000);
#else
        std::chrono::milliseconds(2000);
#endif
        static constexpr size_t PORT = 2022;

        explicit Network();

        bool TryConnect(const std::string &ip);

        static std::vector<char> Compress(const std::string_view &);

        static std::string Decompress(const std::string &data);

    private:
        Response TransferData(const Request &request);

        bool RunFor(std::chrono::steady_clock::duration timeout);

        std::mutex requestsMutex_;
        boost::asio::io_context ioContext_;
        boost::asio::ip::tcp::socket socket_;

    public:

        Response SendReadRequest(ssize_t endpoint);

        Response SendWriteRequest(ssize_t endpoint, const std::string_view &data);

        Response SendReadWriteRequest(ssize_t endpoint, const std::string_view &data);


    };



    template<lib::network::Request::TypeEnum RequestCode>
    requires (RequestCode == Request::TypeEnum::W)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode, const Function& action = [](){}) {

        Function function = [=]() {
            switch (responseCode) {
                case Response::Ok:
                    throw exceptions::InvalidOperationException("Неправильный код возврата");
                case Response::NoContent:
                    action();
                    return;
                case Response::BadRequest:
                    throw exceptions::InvalidOperationException("Возникла ошибка на сервере");
                case Response::ConnectionError:
                    throw exceptions::ConnectionException("Не удалось подключиться к роботу");
                case Response::BufferOverflow:
                    throw exceptions::InvalidOperationException("Слишком большая посылка");
            }
        };

        ExceptionHandler(nullptr, nullptr, function);
    }

    template<lib::network::Request::TypeEnum RequestCode>
    requires (RequestCode == Request::TypeEnum::R)
    void StatusCodeCheck(enum lib::network::Response::CodeEnum responseCode, const Function& action) {
        Function function = [=]() {
            switch (responseCode) {
                case Response::Ok:
                    action();
                    return;
                case Response::NoContent:
                    throw exceptions::InvalidOperationException("Нет данных");
                case Response::BadRequest:
                    throw exceptions::InvalidOperationException("Возникла ошибка на сервере");
                case Response::ConnectionError:
                    throw exceptions::ConnectionException("Не удалось подключиться к роботу");
                case Response::BufferOverflow:
                    throw exceptions::InvalidOperationException("Слишком большая посылка");
            }
        };

        ExceptionHandler(nullptr, nullptr, function);
    }


}

#endif
