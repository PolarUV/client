#ifndef CLIENT_IPFUNCTION_HPP
#define CLIENT_IPFUNCTION_HPP

#include <iphlpapi.h>

#include <string>
#include <vector>
#include <ranges>

[[nodiscard]] inline std::string GetIps() {
    static constexpr size_t ipStructSize = sizeof(IP_ADAPTER_INFO);

    ULONG bufLen = 0;
    GetAdaptersInfo(nullptr, &bufLen);

    std::vector<std::byte> adaptersInfoMemory(bufLen);
    auto *adaptersInfo = reinterpret_cast<IP_ADAPTER_INFO *>(adaptersInfoMemory.data());

    const DWORD result = GetAdaptersInfo(adaptersInfo, &bufLen);

    std::string addresses;
    if (result != NO_ERROR) {
        return addresses;
    }

    addresses.reserve(bufLen / ipStructSize * 16);

    static constexpr std::string_view nullIp = "0.0.0.0";
    for (const auto *currentNode = adaptersInfo; currentNode != nullptr; currentNode = currentNode->Next) {
        for (const auto *currentIp = &(currentNode->IpAddressList); currentIp != nullptr; currentIp = currentIp->Next) {
            if (currentIp->IpAddress.String != nullIp) {
                addresses += currentIp->IpAddress.String;
                addresses += '\0';
            }
        }
    }

    addresses.resize(addresses.size());
    return addresses;
}

class AdaptersInfo {
public:
    [[nodiscard]] const char *data() const { return addresses_.data(); }

    [[nodiscard]] std::array<char, 16> GetIp(int addressId) const {

        std::array<char, 16> addresses;

        auto currentIp = addresses_ | std::views::filter([count = addressId](const char cymbol) mutable {
            if (cymbol == '\0') [[unlikely]] {
                --count;
                return count == -1;
            }
            return count == 0;
        });

        std::copy(currentIp.begin(), currentIp.end(), addresses.begin());

        return addresses;
    }

private:
    const std::string addresses_ = GetIps();
};


#endif
