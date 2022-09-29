#ifndef CLIENT_BASEEXCEPTION_HPP
#define CLIENT_BASEEXCEPTION_HPP

#include <string>

namespace lib::exceptions {

    class BaseException : public std::exception {
    public:
        BaseException(const std::string_view& error, const std::string_view& details) :
                Error(error),
                Details(details){}

        const std::string_view Error;
        const std::string_view Details;
    };
}
#endif
