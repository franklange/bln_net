#pragma once

#include <cstdint>
#include <string>

namespace bln_net::udp {

struct endpoint
{
    endpoint() = default;
    endpoint(std::string, std::uint16_t);

    std::string   addr;
    std::uint16_t port{0};

    auto to_string() const -> std::string;

    auto operator<=>(const endpoint&) const = default;
};

} // namespace bln_net::udp

template<>
struct std::hash<bln_net::udp::endpoint>
{
    auto operator()(const bln_net::udp::endpoint&) const -> std::size_t;
};
