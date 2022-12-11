#pragma once

#include <bln_net/local_endpoint.hpp>
#include <bln_net/types.hpp>

#include <string>

namespace bln_net::local {

struct packet
{
    endpoint remote;
    bytes data;

    auto to_string() const -> std::string;

    auto operator<=>(const packet&) const = default;
};

} // namespace bln_net::local
