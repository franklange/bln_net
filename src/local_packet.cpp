#include <bln_net/local_packet.hpp>

namespace bln_net::local {

auto packet::to_string() const -> std::string
{
    std::string res;
    res.reserve(32);

    res += "[";
    res += remote;
    res += "|b'";
    res += std::to_string(data.size());
    res += "]";

    return res;
}

} // namespace bln_net::local
