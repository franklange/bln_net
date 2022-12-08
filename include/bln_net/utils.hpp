#pragma once

#include <bln_net/types.hpp>
#include <string>

namespace bln_net {

auto to_string(const bln_net::bytes&) -> std::string;
auto to_bytes(const std::string&) -> bln_net::bytes;

} // namespace bln_net
