#include <boost/log/trivial.hpp>
#include "iostream"
#include "Logger.hpp"
#include <boost/stacktrace.hpp>

using namespace lib::logger;

void lib::logger::Setup(){
#if 1
std::clog.rdbuf(std::cout.rdbuf());
#else
static std::fstream output("log.txt", std::ios_base::out | std::ios_base::trunc);
        std::clog.rdbuf(output.rdbuf());
#endif
}

struct Info &Info::operator<<(std::string_view data) {
    if (LogLevel >= LogLevelEnum::Info)
        std::clog << "[INFO] " << data.data();

    return *this;
}


struct Warning &Warning::operator<<(std::string_view data) {
    if (LogLevel >= LogLevelEnum::Warning)
        std::clog << "[WARNING] " << data.data();
    return *this;
}

struct Error &Error::operator<<(std::string_view data) {
    if (LogLevel >= LogLevelEnum::Error)
        std::clog << "[ERROR] " << data.data();
    return *this;
}

struct Critical &Critical::operator<<(std::string_view data) {
    if (logLevel_ >= LogLevelEnum::Critical)
        buf << data.data();
    return *this;
}

lib::logger::Critical::Critical() : buf(){}

lib::logger::Critical::~Critical() {
    if (logLevel_ >= LogLevelEnum::Critical)
        std::clog << "[Critical]" << buf.rdbuf()
                  << "\n[At this point]\n"
                  << boost::stacktrace::stacktrace();
}
