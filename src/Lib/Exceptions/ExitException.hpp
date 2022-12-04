#ifndef CLIENT_EXITEXCEPTION_HPP
#define CLIENT_EXITEXCEPTION_HPP

#include <exception>
#include <string_view>

class ExitException : public std::exception {
   public:
    [[nodiscard]] const char *what() const noexcept override { return message_.data(); }

   private:
    static constexpr std::string_view message_ = "The program is closed by the user";
};

#endif  // CLIENT_EXITEXCEPTION_HPP
