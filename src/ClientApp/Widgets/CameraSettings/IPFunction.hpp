#ifndef CLIENT_IPFUNCTION_HPP
#define CLIENT_IPFUNCTION_HPP

#ifdef WIN32

#include <iphlpapi.h>
#include <list>
#include <string>

[[nodiscard]]
inline std::list<std::string> GetIps() {

    constexpr size_t ipStructSize = sizeof(IP_ADAPTER_INFO);

    std::list<std::string> addresses;

    ULONG bufLen = 0;
    GetAdaptersInfo(nullptr, &bufLen);

    auto adapterInfo = new IP_ADAPTER_INFO[bufLen / ipStructSize];
    DWORD result = GetAdaptersInfo(adapterInfo, &bufLen);

    if (result == NO_ERROR) {

        std::string_view nullIp = "0.0.0.0";

        for (auto currentNode = adapterInfo; currentNode != nullptr; currentNode = currentNode->Next) {

            bool isNullIp = !std::strcmp(nullIp.data(), currentNode->IpAddressList.IpAddress.String);

            if (isNullIp)
                continue;

            addresses.emplace_back(std::string(currentNode->IpAddressList.IpAddress.String));
        }
    }

    delete[] adapterInfo;

    return addresses;
}

#elif UNIX

#include <sys/types.h>
#include <ifaddrs.h>

std::list<std::string> GetIps(){

    char host[NI_MAXHOST];

    std::list<std::string> addresses;

    struct ifaddrs* rawAddresses = nullptr;
    getifaddrs(&rawAddresses);

    for(auto node = rawAddresses; node!= nullptr; node = node->ifa_next){

        if (node->ifa_addr == nullptr)
            continue;

        auto family = node->ifa_addr->sa_family;

        ///if ipv4 addr
        if (family == AF_INET) {
            auto address = (struct sockaddr_in *) (node->ifa_addr);
            addresses.emplace_back(inet_ntoa(address->sin_addr));
        }
    }

    freeifaddrs(rawAddresses);

    return addresses;
}
#endif


#endif