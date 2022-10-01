#ifndef CLIENT_LOGGER_HPP
#define CLIENT_LOGGER_HPP
#include <chrono>
#include <imgui.h>

#include <array>
#include <cassert>
#include <fstream>
#include <sstream>

class Logger {
    constexpr static int MAX_SIZE = 4096;

    std::stringstream localBuffer_;
    std::ofstream& file_;

    static ImGuiTextBuffer& Buffer() {
        static ImGuiTextBuffer buffer;
        return buffer;
    }

    static std::ofstream& File() {
        static std::ofstream file("log.txt", std::ios::trunc);
        return file;
    }

   public:
    static const ImGuiTextBuffer& GetBuffer() { return Buffer(); }

    Logger() : file_(File()) {}

    ~Logger() {
        localBuffer_ << '\n';
        file_ << localBuffer_.rdbuf();

        Buffer().append(localBuffer_.str().c_str());

        if (Buffer().size() > MAX_SIZE) {
            ImGuiTextBuffer newBuf;
            newBuf.append(Buffer().end() - MAX_SIZE, Buffer().end());
            Buffer() = newBuf;
        }
    }

    template <typename T>
    friend Logger&& operator<<(Logger&& logger, const T& value);
};

template <typename T>
Logger&& operator<<(Logger&& logger, const T& value) {
    logger.localBuffer_ << value;
    return std::move(logger);
}

#define PolarPrint(MSG)                                                                                                \
    std::array<char, 16> _str{};                                                                                       \
    const auto _time = std::time(nullptr);                                                                             \
    assert(std::strftime(_str.data(), _str.size(), "%H:%M:%S", std::localtime(&_time)));                               \
    Logger() << _str.data() << " " #MSG " "

#define PolarError PolarPrint([ERROR])
#define PolarWarning PolarPrint([WARNING])
#define PolarDebug PolarPrint([DEBUG])
#define PolarProfile PolarPrint([Profile])

#endif  // CLIENT_LOGGER_HPP
