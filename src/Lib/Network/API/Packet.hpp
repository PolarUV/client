#ifndef CLIENT_PACKET_HPP
#define CLIENT_PACKET_HPP

#include <string>

struct Request {
    enum class TypeEnum : uint64_t { R, W, WR };

    struct HeaderType {
        TypeEnum Type;
        uint64_t EndpointId;
        uint64_t Length;
    };

    Request(const std::string_view &data, TypeEnum type, uint64_t endpointId)
        : Header({type, endpointId, type == TypeEnum::R ? 0 : (data.size())}), Data(data){};

    Request(Request &&) = delete;

    Request(const Request &) = delete;

    const HeaderType Header;
    const std::string_view Data;
};

struct Response {
    enum CodeEnum : uint64_t {
        Ok,
        NoContent,
        BadRequest,
        ConnectionError,
        BufferOverflow,
    };

    struct HeaderType {
        CodeEnum Code{};
        uint64_t EndpointId{};
        uint64_t Length{};

        HeaderType(CodeEnum code, uint64_t endpoint, uint64_t length)
            : Code(code), EndpointId(endpoint), Length(length) {}

        HeaderType() = default;
    };

    Response(std::string &&data, enum CodeEnum code, uint64_t endpointId)
        : Data(std::move(data)), Header(code, endpointId, Data.length()){};

    Response(Response &&response) noexcept : Data(std::move(response.Data)), Header(response.Header) {}

    explicit operator bool() const { return Header.Code == Ok || Header.Code == NoContent; }

    std::string Data;
    const HeaderType Header;
};

#endif
