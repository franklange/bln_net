#pragma once

#include <bln_net/udp_endpoint.hpp>
#include <bln_net/types.hpp>

namespace bln_net::udp {

struct packet
{
    endpoint remote;
    bytes data;

    auto operator<=>(const packet&) const = default;
};

} // namespace bln_net::udp
