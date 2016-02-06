// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "EndPoint.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <cassert>
#include <utility>
#include <array>

namespace somera {
namespace {

sa_family_t ToAddressFamilyPOSIX(AddressFamily family)
{
    switch (family) {
    case AddressFamily::InterNetwork: return AF_INET;
    case AddressFamily::InterNetworkV6: return AF_INET6;
    }
    return AF_INET;
}

} // unnamed namespace

AddressFamily EndPoint::GetFamily() const
{
    return family;
}

EndPoint EndPoint::CreateFromV4(const std::string& internetAddress, uint16_t port)
{
    EndPoint endPoint;
    endPoint.family = AddressFamily::InterNetwork;
    std::memset(&endPoint.address, 0, sizeof(endPoint.address));

    auto & v4 = endPoint.address.asV4;
    v4.sin_family = ToAddressFamilyPOSIX(endPoint.family);
    v4.sin_port = htons(port);
    if (internetAddress.empty()) {
        v4.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else {
        v4.sin_addr.s_addr = ::inet_addr(internetAddress.c_str());
        if (v4.sin_addr.s_addr == 0xffffffff) {
            auto host = ::gethostbyname(internetAddress.c_str());
            if (host == nullptr) {
                throw std::runtime_error("Failed to call gethostbyname");
            }
            v4.sin_addr.s_addr =
                *reinterpret_cast<in_addr_t*>(host->h_addr_list[0]);
        }
    }
    return std::move(endPoint);
}

EndPoint EndPoint::CreateFromV6(uint16_t port, uint32_t scopeId)
{
    EndPoint endPoint;
    endPoint.family = AddressFamily::InterNetworkV6;
    std::memset(&endPoint.address, 0, sizeof(address));
    auto & v6 = endPoint.address.asV6;
    v6.sin6_family = ToAddressFamilyPOSIX(endPoint.family);
    v6.sin6_port = htons(port);
    v6.sin6_scope_id = scopeId;
    return std::move(endPoint);
}

EndPoint EndPoint::CreateFromAddressStorage(const ::sockaddr_storage& storage)
{
    EndPoint endPoint;
    std::memset(&endPoint.address, 0, sizeof(address));

    assert(storage.ss_family == AF_INET || storage.ss_family == AF_INET6);
    if (storage.ss_family == AF_INET) {
        endPoint.family = AddressFamily::InterNetwork;
        endPoint.address.asV4 = *reinterpret_cast<const ::sockaddr_in*>(&storage);
    }
    else if (storage.ss_family == AF_INET6) {
        endPoint.family = AddressFamily::InterNetworkV6;
        endPoint.address.asV6 = *reinterpret_cast<const ::sockaddr_in6*>(&storage);
    }
    return std::move(endPoint);
}

AddressViewPOSIX EndPoint::GetAddressViewPOSIX() const
{
    if (family == AddressFamily::InterNetwork) {
        AddressViewPOSIX view;
        view.data = reinterpret_cast<const ::sockaddr*>(&address.asV4);
        view.size = sizeof(address.asV4);
        return std::move(view);
    }
    assert(family == AddressFamily::InterNetworkV6);
    AddressViewPOSIX view;
    view.data = reinterpret_cast<const ::sockaddr*>(&address.asV6);
    view.size = sizeof(address.asV6);
    return std::move(view);
}

std::string EndPoint::GetAddressNumber() const
{
    if (family == AddressFamily::InterNetwork) {
        return ::inet_ntoa(address.asV4.sin_addr);
    }
    assert(family == AddressFamily::InterNetworkV6);

    std::array<char, INET6_ADDRSTRLEN> numericName;
    std::memset(numericName.data(), 0, numericName.size());

    return ::inet_ntop(
        ToAddressFamilyPOSIX(family),
        &address.asV6.sin6_addr,
        numericName.data(),
        numericName.size());
}

int EndPoint::GetPort() const
{
    if (family == AddressFamily::InterNetwork) {
        return ntohs(address.asV4.sin_port);
    }
    assert(family == AddressFamily::InterNetworkV6);
    return ntohs(address.asV6.sin6_port);
}

} // namespace somera
