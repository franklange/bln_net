#pragma once

#include <bln_net/types.hpp>

#include <chrono>
#include <string_view>
#include <utility>

namespace bln_net {

auto to_string(const bln_net::bytes&) -> std::string;
auto to_bytes(std::string_view) -> bln_net::bytes;

template <typename T>
auto to_duration(T&& t) -> duration
{
    return std::chrono::duration_cast<duration>(std::forward<T>(t));
}

} // namespace bln_net
