#include <bln_net/utils.hpp>

namespace bln_net {

auto to_string(const bln_net::bytes& b) -> std::string
{
    return {b.begin(), b.end()};
}

auto to_bytes(const std::string& s) -> bln_net::bytes
{
    return {s.begin(), s.end()};
}

} // namespace bln_net
