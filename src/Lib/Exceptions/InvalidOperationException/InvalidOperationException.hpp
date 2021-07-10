#ifndef CLIENT_INVALIDOPERATIONEXCEPTION_HPP
#define CLIENT_INVALIDOPERATIONEXCEPTION_HPP

#include "Exceptions/BaseException/BaseException.hpp"

namespace lib::exceptions {
    class InvalidOperationException : public BaseException {
    public:
        explicit InvalidOperationException(const std::string_view& details) : BaseException("Неправильная операция", details) {}
    };
}

#endif
