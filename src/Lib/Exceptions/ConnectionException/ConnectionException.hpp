#ifndef CLIENT_CONNECTIONEXCEPTION_HPP
#define CLIENT_CONNECTIONEXCEPTION_HPP

#include "Exceptions/BaseException/BaseException.hpp"

namespace lib::exceptions {
    class ConnectionException : public BaseException {
    public:
        explicit ConnectionException(const std::string_view& details) : BaseException("Ошибка подключения", details) {}
    };
}

#endif
