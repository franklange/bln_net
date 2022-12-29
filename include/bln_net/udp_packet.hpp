#pragma once

#include <bln_net/udp_endpoint.hpp>
#include <bln_net/types.hpp>

#include <string>

namespace bln_net::udp {

struct packet
{
    endpoint remote{};
    bytes data;

    auto to_string() const -> std::string;

    auto operator<=>(const packet&) const = default;
};

} // namespace bln_net::udp
