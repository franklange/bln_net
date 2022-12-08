#pragma once

#include <cstdint>
#include <string>

namespace bln_net::udp {

struct endpoint
{
    std::string   addr;
    std::uint16_t port;

    auto to_string() const -> std::string;

    auto operator<=>(const endpoint&) const = default;
};

struct ep_hash
{
    auto operator()(const endpoint& e) const -> std::size_t;
};

} // namespace bln_net::udp
