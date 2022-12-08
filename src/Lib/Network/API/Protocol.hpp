#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H

#include "Packet.hpp"

#include <array>

class Network;

/**
 * @brief данный класс отвечает за работу с протоколом и инкапсулирует в себе работу с сетью и компрессором
 */
class Protocol {
public:
    Protocol();

    /**
     * @brief запрос считывающий данные
     *
     * @param[in] endpoint номер эндпоинта для считывающего запроса
     * @return ответ
     */
    Response SendReadRequest(uint64_t endpoint);

    Response SendWriteRequest(const std::string_view &data, uint64_t endpoint);

    Response SendWriteReadRequest(const std::string_view &data, uint64_t endpoint);

    void Connect(const std::array<char, 16>& ip);

    bool IsActive();

private:
    Network *network_;
};

#endif  // CLIENT_NETWORK_H
